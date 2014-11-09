#ifndef LKSTREAMTRANSLATOR_H
#define LKSTREAMTRANSLATOR_H

#include "LKTranslator.h"
#include <yajl_parse.h>
#include <yajl_gen.h>
#include <string>
#include <vector>
#include <sstream>

/**
 * In-stream translator for JSON streams, built on top of
 * [YAJL](https://lloyd.github.io/yajl/).
 * 
 * \warning A Stream Translator object is meant to be used only for a single
 * stream, then discarded; using a single instance to parse multiple streams in
 * succession will throw an exception about "trailing garbage".
 */
class LKStreamTranslator
{
public:
	/// \private Parser context structure.
	struct ctx_t {
		LKTranslator &translator;
		yajl_handle parser;
		yajl_gen gen;
		std::string lastPathComponent;
		std::string currentKey;
	};
	
	/**
	 * Constructs a Stream Translator.
	 * 
	 * @param translator A translator for translating strings in the stream
	 * @param lastPathComponent The last component of the path to this stream,
	 *        for mising line reporting purposes
	 */
	LKStreamTranslator(LKTranslator &translator, std::string lastPathComponent = "");
	
	virtual ~LKStreamTranslator();
	
	
	
	/**
	 * Processes a chunk, making any substitutions necessary and returning it.
	 * 
	 * If the chunk ends in the middle of a value, that value will be withheld
	 * until enough chunks have been fed to the stream parser to complete it.
	 */
	std::vector<char> process(const std::vector<char> &chunk);
	/// \overload
	std::string process(const std::string &string);
	
	
	
	/// \private YAJL Callback to handle null values
	static int handle_null(void *ctx);
	/// \private YAJL Callback to handle boolean values
	static int handle_boolean(void *ctx, int boolVal);
	/// \private YAJL Callback to handle number values
	static int handle_number(void *ctx, const char *numberVal, size_t numberLen);
	/// \private YAJL Callback to handle string values
	static int handle_string(void *ctx, const unsigned char *stringVal, size_t stringLen);
	
	/// \private YAJL Callback to handle the start of a map
	static int handle_start_map(void *ctx);
	/// \private YAJL Callback to handle a key (string) in a map
	static int handle_map_key(void *ctx, const unsigned char *key, size_t stringLen);
	/// \private YAJL Callback to handle the end of a map
	static int handle_end_map(void *ctx);
	
	/// \private YAJL Callback to handle the start of an array
	static int handle_start_array(void *ctx);
	/// \private YAJL Callback to handle the end of an array
	static int handle_end_array(void *ctx);
	
protected:
	/// \private The current parser context
	ctx_t ctx;
	
	/// \private YAJL callback structure
	yajl_callbacks callbacks = { nullptr };
};

#endif
