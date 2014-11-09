#include "LKStreamTranslator.h"
#include <exception>
#include <iostream>

LKStreamTranslator::LKStreamTranslator(LKTranslator &translator, std::string lastPathComponent):
	ctx { translator, nullptr, nullptr, lastPathComponent }
{
	callbacks.yajl_null = &LKStreamTranslator::handle_null;
	callbacks.yajl_boolean = &LKStreamTranslator::handle_boolean;
	callbacks.yajl_number = &LKStreamTranslator::handle_number;
	callbacks.yajl_string = &LKStreamTranslator::handle_string;
	callbacks.yajl_start_map = &LKStreamTranslator::handle_start_map;
	callbacks.yajl_map_key = &LKStreamTranslator::handle_map_key;
	callbacks.yajl_end_map = &LKStreamTranslator::handle_end_map;
	callbacks.yajl_start_array = &LKStreamTranslator::handle_start_array;
	callbacks.yajl_end_array = &LKStreamTranslator::handle_end_array;
	
	ctx.parser = yajl_alloc(&callbacks, NULL, &ctx);
	ctx.gen = yajl_gen_alloc(NULL);
	ctx.translator = translator;
	ctx.lastPathComponent = lastPathComponent;
}

LKStreamTranslator::~LKStreamTranslator()
{
	yajl_free(ctx.parser);
	yajl_gen_free(ctx.gen);
}

std::vector<char> LKStreamTranslator::process(const std::vector<char> &chunk)
{
	std::vector<char> retval;
	
	// We work with C strings here, because YAJL
	const char *str = chunk.data();
	size_t len = chunk.size();
	
	// Skip any BOM if there is one
	const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
	if(memcmp(bom, str, 3) == 0)
	{
		str += 3;
		len -= 3;
	}
	
	// KanColle specific: most datablobs are prefixed with "svdata=", that's
	// needed for the game to work, but we can't parse with it left in
	const char *svdata = "svdata=";
	if(memcmp(svdata, str, strlen(svdata)) == 0)
	{
		str += strlen(svdata);
		len -= strlen(svdata);
		
		retval.insert(retval.end(), svdata, svdata + strlen(svdata));
	}
	
	if(len > 0)
	{
		if(yajl_parse(ctx.parser, (const unsigned char *)str, len) != yajl_status_ok)
		{
			unsigned char *error = yajl_get_error(ctx.parser, true, (const unsigned char *)str, len);
			std::string error_string((const char *)error);
			yajl_free_error(ctx.parser, error);
			
			throw std::runtime_error("JSON Parsing Error: " + error_string);
		}
		
		const unsigned char *buf;
		size_t buf_len;
		yajl_gen_get_buf(ctx.gen, &buf, &buf_len);
		
		if(buf_len > 0)
		{
			retval.insert(retval.end(), buf, buf + buf_len);
			yajl_gen_clear(ctx.gen);
		}
	}
	
	return retval;
}

std::string LKStreamTranslator::process(const std::string &chunk)
{
	std::vector<char> vchunk(chunk.begin(), chunk.end());
	vchunk = process(vchunk);
	return std::string(vchunk.begin(), vchunk.end());
}



int LKStreamTranslator::handle_null(void *ctx) {
	return yajl_gen_null(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_boolean(void *ctx, int val) {
	return yajl_gen_bool(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen, val) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_number(void *ctx, const char *val, size_t len) {
	return yajl_gen_number(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen, val, len) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_string(void *ctx_, const unsigned char *val, size_t len) {
	LKStreamTranslator::ctx_t *ctx = static_cast<LKStreamTranslator::ctx_t*>(ctx_);
	std::string translation = ctx->translator.translate(std::string((const char *)val, len), ctx->lastPathComponent, ctx->currentKey);
	return yajl_gen_string(ctx->gen, (const unsigned char *)translation.c_str(), translation.size()) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_start_map(void *ctx) {
	return yajl_gen_map_open(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_map_key(void *ctx_, const unsigned char *val, size_t len) {
	LKStreamTranslator::ctx_t *ctx = static_cast<LKStreamTranslator::ctx_t*>(ctx_);
	ctx->currentKey = std::string((const char *)val, len);
	return yajl_gen_string(ctx->gen, val, len) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_end_map(void *ctx) {
	return yajl_gen_map_close(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_start_array(void *ctx) {
	return yajl_gen_array_open(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen) == yajl_gen_status_ok;
}

int LKStreamTranslator::handle_end_array(void *ctx) {
	return yajl_gen_array_close(static_cast<LKStreamTranslator::ctx_t*>(ctx)->gen) == yajl_gen_status_ok;
}
