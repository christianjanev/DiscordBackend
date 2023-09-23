#include "pch.h"
#include "ChannelOptions.h"
#include "UserOptions.h"
#include <iostream>

using namespace winrt;

using namespace Windows::Foundation;

using namespace Windows::Web::Http;

using namespace Windows::Security::Cryptography;
using namespace Windows::Security::Credentials;

using namespace Windows::Storage;

void request(UserOptions user) {
    ChannelOptions channel;
    channel.channel_id = L"1131436041606287522";
    channel.server_id = L"989576873258405948";

    HttpClient client;

    auto headers{ client.DefaultRequestHeaders() };
    const std::wstring user_agent = L"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/1.0.76 Chrome/108.0.5359.215 Electron/22.3.24 Safari/537.36";
    if (!headers.UserAgent().TryParseAdd(user_agent)) throw L"Invalid user agent: " + user_agent;
    if (!headers.Accept().TryParseAdd(L"*/*")) throw L"Invalid accept header: */*";
    if (!headers.TryAppendWithoutValidation(L"Authorization", user.token)) throw L"Invalid token";
    headers.Referer() = Uri(L"https://discord.com/channels/" + channel.server_id + L"/" + channel.channel_id);

    HttpResponseMessage response;
    std::wstring response_body;

    try {
        response = client.GetAsync(channel.get_message_url()).get();
        response.EnsureSuccessStatusCode();
        response_body = response.Content().ReadAsStringAsync().get();
    }
    catch (hresult_error const& e) {
        response_body = e.message();
    }
    std::wcout << response_body << std::endl;

}

int main()
{
    init_apartment();

    UserOptions user;
    PasswordVault vault;
    
    PasswordCredential creds = vault.Retrieve(L"Wincord", L"ivanpe12");
    creds.RetrievePassword();
    if (creds.Password().empty()) {
        std::cout << "Enter your username: ";
        std::wcin >> user.name;
        std::cout << "Enter your token: ";
        std::wcin >> user.token;
        vault.Add(PasswordCredential(L"Wincord", user.name, user.token));
    }
    else std::cout << to_string(creds.Password());
}
