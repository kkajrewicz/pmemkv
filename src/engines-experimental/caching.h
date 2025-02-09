/*
 * Copyright 2017-2019, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "../engine.h"

namespace pmem
{
namespace kv
{

class db;

static int ttl; // todo move into private field

class caching : public engine_base {
public:
	caching(void *context, pmemkv_config *config);
	~caching();

	std::string name() final;
	void *engine_context();

	status all(all_callback *callback, void *arg) final;

	status count(std::size_t &cnt) final;

	status each(each_callback *callback, void *arg) final;

	status exists(string_view key) final;

	status get(string_view key, get_callback *callback, void *arg) final;

	status put(string_view key, string_view value) final;

	status remove(string_view key) final;

private:
	bool getString(pmemkv_config *config, const char *key, std::string &str);
	bool readConfig(pmemkv_config *config);
	bool getFromRemoteRedis(const std::string &key, std::string &value);
	bool getFromRemoteMemcached(const std::string &key, std::string &value);
	bool getKey(const std::string &key, std::string &valueField, bool api_flag);

	void *context;
	int attempts;
	db *basePtr;
	std::string host;
	unsigned long int port;
	std::string remoteType;
	std::string remoteUser;
	std::string remotePasswd;
	std::string remoteUrl;
	std::string subEngine;
	std::string subEngineConfig;
};

time_t convertTimeToEpoch(const char *theTime, const char *format = "%Y%m%d%H%M%S");
std::string getTimeStamp(time_t epochTime, const char *format = "%Y%m%d%H%M%S");
bool valueFieldConversion(std::string dateValue);

} /* namespace kv */
} /* namespace pmem */
