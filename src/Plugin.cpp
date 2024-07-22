#include "Plugin.h"
#include <sampapi/CChat.h>
#include <sampapi/CInput.h>
#include <RakHook/rakhook.hpp>
#include <RakNet/StringCompressor.h>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include "BlockPattern.h"
#include "BlockPatternLoader.h"

namespace samp = sampapi::v037r1;
bool bIgnoreMsg = false;
bool bDebugMode = false;
std::vector<BlockPattern> blockPatterns;

Plugin::Plugin(HMODULE hndl) : hModule(hndl) {
    using namespace std::placeholders;
    hookCTimerUpdate.set_cb(std::bind(&Plugin::mainloop, this, _1));
    hookCTimerUpdate.install();
}

template <typename T>
std::string readWithSize(RakNet::BitStream& bs) {
    T size;
    if (!bs.Read(size) || size <= 0)
        return {};
    std::string str(size, '\0');
    bs.Read(str.data(), size);
    return str;
}

template <typename T>
void writeWithSize(RakNet::BitStream& bs, std::string_view str) {
    T size = static_cast<T>(str.size());
    bs.Write(size);
    bs.Write(str.data(), size);
}

bool onServerMessage(unsigned char& id, RakNet::BitStream* bs) {
    if (id != 93) // RPC_ClientMessage
        return true;
    unsigned long color;
    std::string msg;

    // read
    bs->Read(color);
    msg = readWithSize<unsigned int>(*bs);


    if (bIgnoreMsg) {
        for (const auto& pattern : blockPatterns) {
            if (pattern.isMatch(msg, color)) {
                if (bDebugMode) {
                    samp::RefChat() -> AddMessage(0xFF00FF00, ("He bloqueado: " + msg + " Color: " + std::to_string(color)).c_str());
                }
                return false;
            }
        }
    }
    
    if (bDebugMode) {
        msg = "Mensaje: " + msg + " Color: " + std::to_string(color);
        bs->Reset();
        bs->Write(color);
        writeWithSize<unsigned int>(*bs, msg);
    }
    return true;
}

void cmdProc() {
    bIgnoreMsg = !bIgnoreMsg;
    if (bIgnoreMsg) {
        samp::RefChat()->AddMessage(0xFF00FF00, "Activado");
    }
    else {
        samp::RefChat()->AddMessage(0xFF00FF00, "Desactivado");
    }
}

void cmdProcDebug() {
    bDebugMode = !bDebugMode;
    if (bDebugMode) {
        samp::RefChat()->AddMessage(0xFF00FF00, "Debug activado");
    }
    else {
        samp::RefChat()->AddMessage(0xFF00FF00, "Debug desactivado");
    }
}

void cmdReload() {
    blockPatterns = BlockPatternLoader::loadBlockPatterns("smr_config.json");
    samp::RefChat()->AddMessage(0xFF00FF00, "Configuracion recargada");
}

void Plugin::mainloop(const decltype(hookCTimerUpdate)& hook) {
    static bool inited = false;
    if (!inited && samp::RefChat() != nullptr && rakhook::initialize()) {
        using namespace std::placeholders;
        samp::RefChat()->AddMessage(0xFFFFFFFF, "SMR by Hidend Loaded - /smr - /smrd- /smrr");
        samp::RefInputBox()->AddCommand("smr", reinterpret_cast<sampapi::CMDPROC>(cmdProc));
        samp::RefInputBox()->AddCommand("smrd", reinterpret_cast<sampapi::CMDPROC>(cmdProcDebug));
        samp::RefInputBox()->AddCommand("smrr", reinterpret_cast<sampapi::CMDPROC>(cmdReload));
        StringCompressor::AddReference();
        rakhook::on_receive_rpc += onServerMessage;
        blockPatterns = BlockPatternLoader::loadBlockPatterns("smr_config.json");
        inited = true;
    }
    return hook.get_trampoline()();
}
