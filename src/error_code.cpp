/*

Copyright (c) 2008-2014, 2016-2021, Arvid Norberg
Copyright (c) 2017, 2019, Steven Siloti
Copyright (c) 2017, Pavel Pimenov
Copyright (c) 2019-2020, Alden Torres
All rights reserved.

You may use, distribute and modify this code under the terms of the BSD license,
see LICENSE file.
*/

#include "ip2/config.hpp"
#include "ip2/error_code.hpp"
#include "ip2/aux_/string_util.hpp" // for to_string()

#include <sstream>

namespace ip2 {

	struct ip2_error_category final : boost::system::error_category
	{
		const char* name() const BOOST_SYSTEM_NOEXCEPT override;
		std::string message(int ev) const override;
		boost::system::error_condition default_error_condition(int ev) const BOOST_SYSTEM_NOEXCEPT override
		{ return {ev, *this}; }
	};

	const char* ip2_error_category::name() const BOOST_SYSTEM_NOEXCEPT
	{
		return "ip2";
	}

	std::string ip2_error_category::message(int ev) const
	{
		static char const* msgs[] =
		{
			"no error",
			"torrent file collides with file from another torrent",
			"hash check failed",
			"torrent file is not a dictionary",
			"missing or invalid 'info' section in torrent file",
			"'info' entry is not a dictionary",
			"invalid or missing 'piece length' entry in torrent file",
			"missing name in torrent file",
			"invalid 'name' of torrent (possible exploit attempt)",
			"invalid length of torrent",
			"failed to parse files from torrent file",
			"invalid or missing 'pieces' entry in torrent file",
			"incorrect number of piece hashes in torrent file",
			"too many pieces in torrent",
			"invalid metadata received from swarm",
			"invalid bencoding",
			"no files in torrent",
			"invalid escaped string",
			"session is closing",
			"torrent already exists in session",
			"invalid torrent handle used",
			"invalid type requested from entry",
			"missing info-hash from URI",
			"file too short",
			"unsupported URL protocol",
			"failed to parse URL",
			"peer sent 0 length piece",
			"parse failed",
			"invalid file format tag",
			"missing info-hash",
			"mismatching info-hash",
			"invalid hostname",
			"invalid port",
			"port blocked by port-filter",
			"expected closing ] for address",
			"destructing torrent",
			"timed out",
			"upload to upload connection",
			"uninteresting upload-only peer",
			"invalid info-hash",
			"torrent paused",
			"'have'-message with higher index than the number of pieces",
			"bitfield of invalid size",
			"too many piece requests while choked",
			"invalid piece packet",
			"out of memory",
			"torrent aborted",
			"connected to ourselves",
			"invalid piece size",
			"timed out: no interest",
			"timed out: inactivity",
			"timed out: no handshake",
			"timed out: no request",
			"invalid choke message",
			"invalid unchoke message",
			"invalid interested message",
			"invalid not-interested message",
			"invalid request message",
			"invalid hash list",
			"invalid hash piece message",
			"invalid cancel message",
			"invalid dht-port message",
			"invalid suggest piece message",
			"invalid have-all message",
			"invalid have-none message",
			"invalid reject message",
			"invalid allow-fast message",
			"invalid extended message",
			"invalid message",
			"sync hash not found",
			"unable to verify encryption constant",
			"plaintext mode not provided",
			"rc4 mode not provided",
			"unsupported encryption mode",
			"peer selected unsupported encryption mode",
			"invalid encryption pad size",
			"invalid encryption handshake",
			"incoming encrypted connections disabled",
			"incoming regular connections disabled",
			"duplicate peer-id",
			"torrent removed",
			"packet too large",
			"",
			"HTTP error",
			"missing location header",
			"invalid redirection",
			"redirecting",
			"invalid HTTP range",
			"missing content-length",
			"banned by IP filter",
			"too many connections",
			"peer banned",
			"stopping torrent",
			"too many corrupt pieces",
			"torrent is not ready to accept peers",
			"peer is not properly constructed",
			"session is closing",
			"optimistic disconnect",
			"torrent finished",
			"no router found",
			"metadata too large",
			"invalid metadata request",
			"invalid metadata size",
			"invalid metadata offset",
			"invalid metadata message",
			"pex message too large",
			"invalid pex message",
			"invalid lt_tracker message",
			"pex messages sent too frequent (possible attack)",
			"torrent has no metadata",
			"invalid dont-have message",
			"SSL connection required",
			"invalid SSL certificate",
			"not an SSL torrent",
			"banned by port filter",
			"invalid session handle used",
			"listen socket has been closed",
			"invalid hash request",
			"invalid hashes",
			"invalid hash reject",

// natpmp errors
			"unsupported protocol version",
			"not authorized to create port map (enable NAT-PMP on your router)",
			"network failure",
			"out of resources",
			"unsupported opcode",
			"",
			"",
			"",
			"",
			"",

// fastresume errors
			"missing or invalid 'file sizes' entry",
			"no files in resume data",
			"missing 'slots' and 'pieces' entry",
			"mismatching number of files",
			"mismatching file size",
			"mismatching file timestamp",
			"not a dictionary",
			"invalid 'blocks per piece' entry",
			"missing slots list",
			"file has more slots than torrent",
			"invalid entry type in slot list",
			"invalid piece index in slot list",
			"pieces needs to be reordered",
			"fastresume not modified since last save",
			"too many duplicate filenames",
			"",
			"",
			"",
			"",
			"",

// HTTP errors
			"Invalid HTTP header",
			"missing Location header in HTTP redirect",
			"failed to decompress HTTP response",
			"",
			"",
			"",
			"",
			"",
			"",
			"",

// i2p errors
			"no i2p router is set up",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",

// tracker errors
			"scrape not available on tracker",
			"invalid tracker response",
			"invalid peer dictionary entry",
			"tracker sent a failure message",
			"missing or invalid 'files' entry",
			"missing or invalid 'hash' entry",
			"missing or invalid 'peers' and 'peers6' entry",
			"udp tracker response packet has invalid size",
			"invalid transaction id in udp tracker response",
			"invalid action field in udp tracker response",
			"skipping tracker announce (unreachable)",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",

#if TORRENT_ABI_VERSION == 1
// bdecode errors
			"expected string in bencoded string",
			"expected colon in bencoded string",
			"unexpected end of file in bencoded string",
			"expected value (list, dict, int or string) in bencoded string",
			"bencoded nesting depth exceeded",
			"bencoded item count limit exceeded",
			"integer overflow",
			"",
			"",
			"",
#else
			"", "", "", "", "",
			"", "", "", "", "",
#endif
			"random number generator failed",
			"blocked by SSRF mitigation",
			"blocked by IDNA ban",
			"",
			"",
			"",
			"",
			"",
			"",
			"",

			"the torrent file has an unknown meta version",
			"the v2 torrent file has no file tree",
			"the torrent contains v2 keys but does not specify meta version 2",
			"the v1 and v2 file metadata does not match",
			"one or more files are missing piece layer hashes",
			"a piece layer is invalid",
			"a v2 file entry has no root hash",
			"v1 and v2 hashes do not describe the same data",
			"a file in the v2 metadata has the pad attribute set"
		};
		if (ev < 0 || ev >= int(sizeof(msgs)/sizeof(msgs[0])))
			return "Unknown error";
		return msgs[ev];
	}

	boost::system::error_category& ip2_category()
	{
		static ip2_error_category ip2_category;
		return ip2_category;
	}

	struct http_error_category final : boost::system::error_category
	{
		const char* name() const BOOST_SYSTEM_NOEXCEPT override
		{ return "http"; }
		std::string message(int ev) const override
		{
			std::string ret;
			ret += aux::to_string(ev).data();
			ret += ' ';
			switch (ev)
			{
				case errors::cont: ret += "Continue"; break;
				case errors::ok: ret += "OK"; break;
				case errors::created: ret += "Created"; break;
				case errors::accepted: ret += "Accepted"; break;
				case errors::no_content: ret += "No Content"; break;
				case errors::multiple_choices: ret += "Multiple Choices"; break;
				case errors::moved_permanently: ret += "Moved Permanently"; break;
				case errors::moved_temporarily: ret += "Moved Temporarily"; break;
				case errors::not_modified: ret += "Not Modified"; break;
				case errors::bad_request: ret += "Bad Request"; break;
				case errors::unauthorized: ret += "Unauthorized"; break;
				case errors::forbidden: ret += "Forbidden"; break;
				case errors::not_found: ret += "Not Found"; break;
				case errors::internal_server_error: ret += "Internal Server Error"; break;
				case errors::not_implemented: ret += "Not Implemented"; break;
				case errors::bad_gateway: ret += "Bad Gateway"; break;
				case errors::service_unavailable: ret += "Service Unavailable"; break;
				default: ret += "(unknown HTTP error)"; break;
			}
			return ret;
		}
		boost::system::error_condition default_error_condition(
			int ev) const BOOST_SYSTEM_NOEXCEPT override
		{ return {ev, *this}; }
	};

	boost::system::error_category& http_category()
	{
		static http_error_category http_category;
		return http_category;
	}

	namespace errors
	{
		// hidden
		boost::system::error_code make_error_code(error_code_enum e)
		{
			return {e, ip2_category()};
		}
	}

	std::string print_error(error_code const& ec)
	{
		if (!ec) return {};
		std::stringstream ret;
		ret << "ERROR: (" << ec.category().name() << ":" << ec.value() << ") "
			<< ec.message();
		return ret.str();
	}

}