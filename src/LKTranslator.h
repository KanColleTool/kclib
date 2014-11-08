#ifndef KCLIB_LKTRANSLATOR_H
#define KCLIB_LKTRANSLATOR_H

#include <functional>
#include <map>
#include <string>

/**
 * Handles translation of lines via a crc32 lookup table.
 */
class LKTranslator
{
public:
	/**
	 * A possible loading state for the translation data.
	 */
	enum LoadStatus {
		LoadStatusNotLoaded,	///< No attempt to load the data has been made.
		LoadStatusLoading,		///< Data is currently loading.
		LoadStatusLoaded,		///< Data is fully loaded.
		LoadStatusError			///< Data loading failed with an error.
	};
	
	/**
	 * Translates the given line, according to the current translation data.
	 * 
	 * @see loadStatus
	 * @see reportCallback
	 * 
	 * @param line The line to be translated. Encoding doesn't really matter,
	 *        as translation is done with binary crc32 sums.
	 * @param lastPathComponent The last component of the path to the endpoint
	 *        where the string was encountered.
	 * @param jsonKey The key for the line in the document it was encountered,
	 *        provided for translation context and blacklisting.
	 * 
	 * @returns The translated string, or the original one if there is no
	 *          translation available.
	 */
	std::string translate(std::string line, std::string lastPathComponent = "", std::string jsonKey = "");
	
	/**
	 * Current load status for the translation data.
	 * 
	 * This should be set externally by your program, as kclib has no
	 * networking facilities of its own.
	 */
	LoadStatus loadStatus = LoadStatusNotLoaded;
	
	/**
	 * Current translation data.
	 * Keys are crc32 sums of untranslated lines, and values are the lines'
	 * translated equivalents.
	 * 
	 * This should be set externally by your program, as kclib has no
	 * networking facilities of its own.
	 */
	std::map<uint32_t, std::string> translationData;
	
	/**
	 * Callback for reporting untranslated lines.
	 */
	std::function<void(std::string line, std::string lastPathComponent, std::string key)> reportCallback;
};

#endif
