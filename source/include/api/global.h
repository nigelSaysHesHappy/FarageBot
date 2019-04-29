#ifndef _FARAGE_GLOBAL_
#define _FARAGE_GLOBAL_

#define FARAGE_DEFAULT_PREFIX               "!"

#include "api/internal.h"
#include "api/admins.h"
#include <mutex>
#include <atomic>

namespace Farage
{
    class Handle;
    class GlobVar;
    
    class Global
    {
        public:
            Global(std::string version, Internals cbs) : engineVer(version), callbacks(cbs) {}
            std::unordered_map<std::string,AdminFlag> admins;
            std::unordered_map<std::string,std::unordered_map<std::string,AdminFlag>> adminRoles;
            std::vector<Handle*> plugins;
            std::vector<GlobVar*> globVars;
            std::unordered_map<std::string,std::string> prefixes;
            std::string prefix(const std::string &guild_id = "default");
            bool verbose;
            bool debug;
            std::vector<std::string> ignoredChannels;
            std::vector<std::string> ignoredUsers;
            std::string selfID;
            void *discord;
            inline std::string engineVersion() { return engineVer; }
            AdminFlag getAdminFlags(const std::string &userID);
            AdminFlag getAdminFlags(const std::string &guildID, const std::string &userID);
            AdminFlag getAdminRoleFlags(const std::string &guildID, const std::string &roleID);
            Internals callbacks;
            inline bool bufferIsLocked() { return isLocked; }
            void clearBuffer()
            {
                bufferLock.lock();
                isLocked = true;
                consoleBuffer.clear();
                bufferLock.unlock();
                isLocked = false;
            }
            std::vector<std::string>* getBuffer()
            {
                bufferLock.lock();
                isLocked = true;
                return &consoleBuffer;
            }
            inline void returnBuffer()
            {
                bufferLock.unlock();
                isLocked = false;
            }
            
        private:
            std::atomic<bool> isLocked;
            std::mutex bufferLock;
            std::string engineVer;
            std::vector<std::string> consoleBuffer;
    };
};

#endif

