#pragma once
#include "pch.h"
#include <string>

#define DISCORD_ENDPOINT L"https://discord.com/api/v9"

using namespace winrt::Windows::Foundation;

class ChannelOptions {
	public:
		std::wstring channel_id;
		std::wstring server_id;

		Uri get_message_url() {
			std::wstring url = DISCORD_ENDPOINT"/channels/";
			url += channel_id;
			url += L"/messages?limit=50";
			return Uri(url);
		}
};
