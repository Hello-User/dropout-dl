#pragma once

#include <iostream>

#include <curl/curl.h>

#ifdef DROPOUT_DL_GCRYPT
#include <gcrypt.h>
#endif


namespace dropout_dl {
	/**
	 *
	 * @param string - The string which is being searched
	 * @param start - The starting index of the substring
	 * @param test_str - The string which is being tested
	 * @return whether or not the substring is at the start index
	 *
	 * Checks if <b>test_str</b> is a substring of <b>string</b> at the start index
	 */
	bool substr_is(const std::string& string, int start, const std::string& test_str);



	/**
	 *
	 * @param str - The base string which is being modified
	 * @param from - what is being replaced
	 * @param to - what to place it with
	 *
	 * Replaces every instance of the <b>from</b> string with the <b>to</b> string.
	 */
	void replace_all(std::string& str, const std::string& from, const std::string& to);

	/**
	 *
	 * @param str - A string
	 * @return <b>str</b> with any leading or following whitespace
	 *
	 * Removes leading and following whitespace from a string and returns the modified string
	 */
	std::string remove_leading_and_following_whitespace(const std::string& str);

	/**
	 *
	 * @param str - A string
	 * @return <b>str</b> with any html character codes replaced with their ascii equivalent.
	 *
	 * E.G. \&#39; would be replaced with '
	 */
	std::string replace_html_character_codes(const std::string& str);

	/**
	 *
	 * @param str - A string
	 * @return <b>str</b> with junk removed or replace
	 *
	 * Removed leading and following whitespace and replaces html character codes
	 */
	std::string format_name_string(const std::string& str);

	/**
	 *
	 * @param str - A string
	 * @return <b>str</b> properly formatted to be a filename
	 *
	 * Removes non-alphanumeric characters and spaces
	 */
	std::string format_filename(const std::string& str);

	#if defined(__WIN32__)
	#include <windows.h>
	msec_t time_ms(void);
	#else
	#include <sys/time.h>
	/**
	 *
	 * @return The time in milliseconds
	 */
	long time_ms();
	#endif

	/**
	 *
	 * @param filename - Name of the file that is being downloaded
	 * @param total_to_download - The total amount of bytes that are being downloaded
	 * @param downloaded - The current amount of bytes that have been downloaded
	 * @param total_to_upload - The total amount of bytes that are being uploaded (This project does not upload so this is not used)
	 * @param uploaded - The current amount of bytes that have been uploaded (This project does not upload so this is not used)
	 * @return 0
	 *
	 * Used by curl. Displays the filename followed by a bar which show the percent downloaded followed by the number of Mib downloaded out of the total.
	 * The function takes the upload amount because that is required by curl but they are just ignored for this since we never upload anything.
	 */
	int curl_progress_func(void* filename, curl_off_t total_to_download, curl_off_t downloaded, curl_off_t total_to_upload, curl_off_t uploaded);

	/**
	 *
	 * @param contents - What we're writing
	 * @param size - The amount that is being written
	 * @param nmemb - The number of bytes per unit of size
	 * @param userp - Where the information in <b>contents</b> is written to
	 * @return size * nmemb
	 *
	 * Used by curl. Writes the information gathered by curl into the userp string. This function was not written by me.
	 */
	size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

	/**
	 *
	 * @param url - Url which is being downloaded
	 * @param verbose - Whether or not to be verbose (not recommended)
	 * @return The page data as a string
	 *
	 * This function downloads the provided url and returns it as a string. Does not use cookies. This was ripped directly from a firefox network request for an episode page and modified minimally.
	 */
	std::string get_generic_page(const std::string& url, bool verbose = false);

}
