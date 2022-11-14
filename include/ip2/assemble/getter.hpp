/*

Copyright (c) 2022, Xianshui Sheng
All rights reserved.

You may use, distribute and modify this code under the terms of the BSD license,
see LICENSE file.
*/

#ifndef IP2_ASSEMBLE_GETTER_HPP
#define IP2_ASSEMBLE_GETTER_HPP

#include "ip2/assemble/assemble_logger.hpp"
#include "ip2/assemble/get_context.hpp"
#include "ip2/assemble/rpc_params_config.hpp"

#include <ip2/entry.hpp>
#include <ip2/io_context.hpp>
#include "ip2/api/error_code.hpp"
#include "ip2/aux_/session_interface.hpp"
#include "ip2/aux_/common.h"
#include "ip2/aux_/deadline_timer.hpp"
#include "ip2/span.hpp"
#include "ip2/uri.hpp"

#include <ip2/kademlia/types.hpp>
#include <ip2/kademlia/item.hpp>
#include <ip2/kademlia/node_entry.hpp>

#include <functional>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace ip2::api;

namespace ip2 {

namespace aux {
    struct session_settings;
}

namespace assemble {

static constexpr int handle_incoming_relay_period = 500; // milliseconds

static constexpr int incoming_relay_limit = 500;

static constexpr int tasks_concurrency_limit = 2;

struct incoming_relay_req
{
	dht::public_key sender;
	aux::uri blob_uri;
	dht::timestamp ts;

	incoming_relay_req(dht::public_key const& s, aux::uri const& u, dht::timestamp t)
		: sender(s), blob_uri(u), ts(t)
	{}
};

class TORRENT_EXTRA_EXPORT getter final
	: std::enable_shared_from_this<getter>
{
public:
	getter(io_context& ios
		, aux::session_interface& session
		, aux::session_settings const& settings
		, counters& cnt
		, assemble_logger& logger);

	getter(getter const&) = delete;
	getter& operator=(getter const&) = delete;
	getter(getter&&) = delete;
	getter& operator=(getter&&) = delete;

	std::shared_ptr<getter> self() { return shared_from_this(); }

	void start();
	void stop();

	void on_incoming_relay_request(dht::public_key const& sender
		, aux::uri blob_uri, dht::timestamp ts);

	void update_node_id();

private:

	void get_callback(dht::item const& it, bool auth
		, std::shared_ptr<get_context> ctx, sha1_hash seg_hash);

	void handle_incoming_relay_timeout(error_code const& e);

	void start_getting_task(incoming_relay_req const& task);
	void drop_incoming_relay_task(incoming_relay_req const& task);

	io_context& m_ios;
	aux::session_interface& m_session;
	aux::session_settings const& m_settings;
	counters& m_counters;

	assemble_logger& m_logger;

	dht::public_key m_self_pubkey;

	std::queue<incoming_relay_req> m_incoming_tasks;

	std::set<std::shared_ptr<get_context> > m_running_tasks;

	aux::deadline_timer m_handle_incoming_relay_timer;

	bool m_running = false;
};

} // namespace assemble
} // namespace ip2

#endif // IP2_ASSEMBLE_GETTER_HPP