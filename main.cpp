#include <iostream>
#include <cstdlib>
#include <string>
#include  "create_service.h"

struct QueryOptions {
    std::string serverName;
    std::string serviceName;
    std::string typeEnumerate = "service";   // Allowed: driver, service, all
    std::string typeDetail = "own";          // Allowed: own, share, interact, kernel, filesys, rec, adapt
    std::string state = "active";            // Allowed: active, inactive, all
    int bufsize = 1024;
    int resumeIndex = 0;
    std::string group = "";
};

struct QdescriptionOptions {
    std::string serverName;
    std::string serviceName;
    int bufsize = 1024; // Default buffer size
};

struct StartOptions {
    std::string serverName;
    std::string serviceName;
    std::string serviceArguments; // Optional arguments to pass to the service.
};

struct StopOptions {
    std::string serverName;
    std::string serviceName;
};

struct ConfigOptions {
    std::string serverName;
    std::string serviceName;
    std::string serviceType = "own";    // Default: own
    std::string interactType = "";      // Only applicable if serviceType is "interact"
    std::string startType = "demand";     // Default: demand
    std::string errorControl = "normal";  // Default: normal
    std::string binpath = "";           // Must be provided if applicable
    std::string group = "";             // Default: empty (null)
    std::string tag = "no";             // Default: no
    std::string depend = "";
    std::string obj = "LocalSystem";    // Default: LocalSystem
    std::string displayname = "";
    std::string password = "";
};

// Structure for "failure" options.
struct FailureOptions {
    std::string serverName;
    std::string serviceName;
    int reset = 0;              // Default: 0 (not set)
    std::string reboot = "";    // Default: empty
    std::string command = "";   // Default: empty
    std::string actions = "";   // Default: empty
};

// Function to display help text.
void printHelp() {
    std::cout << "Usage:\n";
    std::cout << "  sc.exe [<servername>] query [<servicename>] [options]\n";
    std::cout << "  sc.exe [<servername>] create [<servicename>] [options]\n\n";
    
    std::cout << "Global Parameters:\n";
    std::cout << "  <servername>  : UNC name of the remote server (e.g. \\\\myserver).\n";
    std::cout << "  <servicename> : Service name.\n\n";
    
    std::cout << "Query Options:\n";
    std::cout << "  type= {driver|service|all} or type= {own|share|interact|kernel|filesys|rec|adapt}\n";
    std::cout << "  state= {active|inactive|all}\n";
    std::cout << "  bufsize= <Buffersize>\n";
    std::cout << "  ri= <Resumeindex>\n";
    std::cout << "  group= <Groupname>\n\n";
    
    std::cout << "Create Options:\n";
    std::cout << "  type= {own|share|kernel|filesys|rec|interact} [type= {own|share} if first is interact]\n";
    std::cout << "  start= {boot|system|auto|demand|disabled|delayed-auto}\n";
    std::cout << "  error= {normal|severe|critical|ignore}\n";
    std::cout << "  binpath= <binarypathname>\n";
    std::cout << "  group= <loadordergroup>\n";
    std::cout << "  tag= {yes|no}\n";
    std::cout << "  depend= <dependencies>\n";
    std::cout << "  obj= {<accountname>|<objectname>}\n";
    std::cout << "  displayname= <displayname>\n";
    std::cout << "  password= <password>\n\n";
    
    std::cout << "  /? : Displays this help message\n";
}

void query(const QueryOptions &opts) {
    std::cout << "Called query() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Type Enumerate: " << opts.typeEnumerate << "\n";
    std::cout << "  Type Detail: " << opts.typeDetail << "\n";
    std::cout << "  State: " << opts.state << "\n";
    std::cout << "  Buffer Size: " << opts.bufsize << "\n";
    std::cout << "  Resume Index: " << opts.resumeIndex << "\n";
    std::cout << "  Group: " << opts.group << "\n";
}

/*
void create(const CreateOptions &opts) {
    std::cout << "Called create() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Service Type: " << opts.serviceType;
    if (opts.serviceType == "interact") {
        std::cout << " (" << opts.interactType << ")";
    }
    std::cout << "\n";
    std::cout << "  Start Type: " << opts.startType << "\n";
    std::cout << "  Error Control: " << opts.errorControl << "\n";
    std::cout << "  Binpath: " << opts.binpath << "\n";
    std::cout << "  Group: " << opts.group << "\n";
    std::cout << "  Tag: " << opts.tag << "\n";
    std::cout << "  Depend: " << opts.depend << "\n";
    std::cout << "  Obj: " << opts.obj << "\n";
    std::cout << "  Display Name: " << opts.displayname << "\n";
    std::cout << "  Password: " << opts.password << "\n";
}
*/

void qdescription(const QdescriptionOptions &opts) {
    std::cout << "Called qdescription() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Buffer Size: " << opts.bufsize << "\n";
}


void startService(const StartOptions &opts) {
    std::cout << "Called start() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Service Arguments: " << opts.serviceArguments << "\n";
}

void stopService(const StopOptions &opts) {
    std::cout << "Called stop() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
}

void config(const ConfigOptions &opts) {
    std::cout << "Called config() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Service Type: " << opts.serviceType;
    if (opts.serviceType == "interact") {
        std::cout << " (" << opts.interactType << ")";
    }
    std::cout << "\n";
    std::cout << "  Start Type: " << opts.startType << "\n";
    std::cout << "  Error Control: " << opts.errorControl << "\n";
    std::cout << "  Binpath: " << opts.binpath << "\n";
    std::cout << "  Group: " << opts.group << "\n";
    std::cout << "  Tag: " << opts.tag << "\n";
    std::cout << "  Depend: " << opts.depend << "\n";
    std::cout << "  Obj: " << opts.obj << "\n";
    std::cout << "  Display Name: " << opts.displayname << "\n";
    std::cout << "  Password: " << opts.password << "\n";
}

// Placeholder function for "failure" subcommand.
void failure(const FailureOptions &opts) {
    std::cout << "Called failure() with options:\n";
    std::cout << "  Server Name: " << (opts.serverName.empty() ? "Local" : opts.serverName) << "\n";
    std::cout << "  Service Name: " << opts.serviceName << "\n";
    std::cout << "  Reset: " << opts.reset << "\n";
    std::cout << "  Reboot: " << opts.reboot << "\n";
    std::cout << "  Command: " << opts.command << "\n";
    std::cout << "  Actions: " << opts.actions << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return EXIT_FAILURE;
    }
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "/?" || arg == "-?" || arg == "/help" || arg == "-help") {
            printHelp();
            return EXIT_SUCCESS;
        }
    }
    
    int index = 1;
    std::string globalServerName = "";
    std::string subcommand = "";
    
    std::string firstArg = argv[index];
    if (firstArg == "query" || firstArg == "create" || firstArg == "qdescription" || firstArg == "start" || firstArg == "stop" || firstArg == "config" || firstArg == "failure") {
        subcommand = firstArg;
        index++;
    } else {
        globalServerName = firstArg;
        index++;
        if (index >= argc) {
            std::cerr << "Missing subcommand after server name\n";
            return EXIT_FAILURE;
        }
        subcommand = argv[index];
        index++;
    }
    
    // get service name
    std::string globalServiceName = "";
    if (index < argc) {
        std::string potentialServiceName = argv[index];
        if (potentialServiceName.find('=') == std::string::npos) {
            globalServiceName = potentialServiceName;
            index++;
        }
    }
    
    if (subcommand == "query") {
        QueryOptions opts;
        opts.serverName = globalServerName;
        opts.serviceName = globalServiceName;
        
        for (; index < argc; index++) {
            std::string arg = argv[index];
            size_t pos = arg.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Unexpected argument: " << arg << "\n";
                continue;
            }
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            
            if (key == "type") {
                if (value == "driver" || value == "service" || value == "all") {
                    opts.typeEnumerate = value;
                } else if (value == "own" || value == "share" || value == "interact" ||
                           value == "kernel" || value == "filesys" || value == "rec" || value == "adapt") {
                    opts.typeDetail = value;
                } else {
                    std::cerr << "Unknown type value for query: " << value << "\n";
                }
            } else if (key == "state") {
                opts.state = value;
            } else if (key == "bufsize") {
                try {
                    opts.bufsize = std::stoi(value);
                } catch (...) {
                    std::cerr << "Invalid bufsize value: " << value << "\n";
                }
            } else if (key == "ri") {
                try {
                    opts.resumeIndex = std::stoi(value);
                } catch (...) {
                    std::cerr << "Invalid resume index value: " << value << "\n";
                }
            } else if (key == "group") {
                opts.group = value;
            } else {
                std::cerr << "Unknown parameter for query: " << key << "\n";
            }
        }
        query(opts);
    } else if (subcommand == "create") {
        CreateOptions opts;
        opts.serverName = globalServerName;
        opts.serviceName = globalServiceName;
        
        for (; index < argc; index++) {
            std::string arg = argv[index];
            size_t pos = arg.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Unexpected argument: " << arg << "\n";
                continue;
            }
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            
            if (key == "type") {
                // first is service type, then interact type
                if (opts.serviceType.empty()) {
                    opts.serviceType = value;
                } else if (opts.serviceType == "interact" && opts.interactType.empty()) {
                    opts.interactType = value;
                    if (value != "own" && value != "share") {
                        std::cerr << "Invalid interact type (must be own or share): " << value << "\n";
                    }
                } else {
                    std::cerr << "Unexpected duplicate type parameter: " << value << "\n";
                }
            } else if (key == "start") {
                opts.startType = value;
            } else if (key == "error") {
                opts.errorControl = value;
            } else if (key == "binpath") {
                opts.binpath = value;
            } else if (key == "group") {
                opts.group = value;
            } else if (key == "tag") {
                opts.tag = value;
            } else if (key == "depend") {
                opts.depend = value;
            } else if (key == "obj") {
                opts.obj = value;
            } else if (key == "displayname") {
                opts.displayname = value;
            } else if (key == "password") {
                opts.password = value;
            } else {
                std::cerr << "Unknown parameter for create: " << key << "\n";
            }
        }
        createService(opts);
    } else if (subcommand == "qdescription") {
    QdescriptionOptions opts;
    opts.serverName = globalServerName;
    
    if (globalServiceName.empty() && index < argc) {
        std::string potentialServiceName = argv[index];
        if (potentialServiceName.find('=') == std::string::npos) {
            opts.serviceName = potentialServiceName;
            index++;
        }
    } else {
        opts.serviceName = globalServiceName;
    }
    
    // optional positional, buffersize
    if (index < argc) {
        std::string bufArg = argv[index];
        try {
            opts.bufsize = std::stoi(bufArg);
        } catch (...) {
            std::cerr << "Invalid buffer size: " << bufArg << "\n";
        }
        index++;
    }
    
    // no more params
    for (; index < argc; index++) {
        std::cerr << "Unexpected argument for qdescription: " << argv[index] << "\n";
    }
    

    qdescription(opts);
    } else if (subcommand == "start") {
        StartOptions opts;
        opts.serverName = globalServerName;
        
        if (globalServiceName.empty() && index < argc) {
            opts.serviceName = argv[index];
            index++;
        } else if (!globalServiceName.empty()) {
            opts.serviceName = globalServiceName;
        } else {
            std::cerr << "Missing service name for start command.\n";
            return EXIT_FAILURE;
        }
        
        // optional positional, args (it will only take the next one so it'll just work on stuff put inside quotes)
        if (index < argc) {
            opts.serviceArguments = argv[index];
            index++;
        }
        
        // no more params
        for (; index < argc; index++) {
            std::cerr << "Unexpected argument for start: " << argv[index] << "\n";
        }
        
        startService(opts);
    } else if (subcommand == "stop") {
        StopOptions opts;
        opts.serverName = globalServerName;
        
        if (globalServiceName.empty() && index < argc) {
            opts.serviceName = argv[index];
            index++;
        } else if (!globalServiceName.empty()) {
            opts.serviceName = globalServiceName;
        } else {
            std::cerr << "Missing service name for stop command.\n";
            return EXIT_FAILURE;
        }
        
        // no more params
        for (; index < argc; index++) {
            std::cerr << "Unexpected argument for stop: " << argv[index] << "\n";
        }
        
        stopService(opts);
    } else if (subcommand == "config") {
        ConfigOptions opts;
        opts.serverName = globalServerName;
        
        if (globalServiceName.empty() && index < argc) {
            std::string potentialServiceName = argv[index];
            if (potentialServiceName.find('=') == std::string::npos) {
                opts.serviceName = potentialServiceName;
                index++;
            }
        } else {
            opts.serviceName = globalServiceName;
        }
        
        for (; index < argc; index++) {
            std::string arg = argv[index];
            size_t pos = arg.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Unexpected argument for config: " << arg << "\n";
                continue;
            }
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            
            if (key == "type") {
                // first time service, next time interactive
                /* TODO Change how interact and sub types are handled. This is fucking cringe */
                if (opts.serviceType == "own" && value != "interact") {
                    opts.serviceType = value;
                } else if (value == "interact") {
                    opts.serviceType = "interact";
                } else if (opts.serviceType == "interact" && opts.interactType.empty()) {
                    opts.interactType = value;
                    if (value != "own" && value != "share") {
                        std::cerr << "Invalid interact type (must be own or share): " << value << "\n";
                    }
                } else {
                    std::cerr << "Unexpected duplicate or invalid type parameter: " << value << "\n";
                }
            } else if (key == "start") {
                opts.startType = value;
            } else if (key == "error") {
                opts.errorControl = value;
            } else if (key == "binpath") {
                opts.binpath = value;
            } else if (key == "group") {
                opts.group = value;
            } else if (key == "tag") {
                opts.tag = value;
            } else if (key == "depend") {
                opts.depend = value;
            } else if (key == "obj") {
                opts.obj = value;
            } else if (key == "displayname") {
                opts.displayname = value;
            } else if (key == "password") {
                opts.password = value;
            } else {
                std::cerr << "Unknown parameter for config: " << key << "\n";
            }
        }
        
        config(opts);
    } else if (subcommand == "failure") {
        FailureOptions opts;
        opts.serverName = globalServerName;
        
        if (globalServiceName.empty() && index < argc) {
            std::string potentialServiceName = argv[index];
            if (potentialServiceName.find('=') == std::string::npos) {
                opts.serviceName = potentialServiceName;
                index++;
            }
        } else {
            opts.serviceName = globalServiceName;
        }
        
        for (; index < argc; index++) {
            std::string arg = argv[index];
            size_t pos = arg.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Unexpected argument for failure: " << arg << "\n";
                continue;
            }
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            
            if (key == "reset") {
                try {
                    opts.reset = std::stoi(value);
                } catch (...) {
                    std::cerr << "Invalid reset value: " << value << "\n";
                }
            } else if (key == "reboot") {
                opts.reboot = value;
            } else if (key == "command") {
                opts.command = value;
            } else if (key == "actions") {
                opts.actions = value;
            } else {
                std::cerr << "Unknown parameter for failure: " << key << "\n";
            }
        }
        
        failure(opts);
    }
    else {
        std::cerr << "Unknown subcommand: " << subcommand << "\n";
        printHelp();
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

