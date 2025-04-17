#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

struct BinderTransaction {
    std::string from;
    std::string to;
    int code;
    std::string timestamp;
};

void parse_log(const std::string& log_path, std::vector<BinderTransaction>& transactions) {
    std::ifstream infile(log_path);
    std::string line;
    std::regex pattern(R"(\[(.*?)\] (\w+): call from (.+) to (.+) code (\d+))");

    while (std::getline(infile, line)) {
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            BinderTransaction tx;
            tx.timestamp = match[1];
            tx.from = match[3];
            tx.to = match[4];
            tx.code = std::stoi(match[5]);
            transactions.push_back(tx);
        }
    }
}

void output_json(const std::vector<BinderTransaction>& txs) {
    std::cout << "[\n";
    for (size_t i = 0; i < txs.size(); ++i) {
        const auto& tx = txs[i];
        std::cout << "  {\n"
                  << "    \"from\": \"" << tx.from << "\",\n"
                  << "    \"to\": \"" << tx.to << "\",\n"
                  << "    \"code\": " << tx.code << ",\n"
                  << "    \"timestamp\": \"" << tx.timestamp << "\"\n"
                  << "  }" << (i + 1 < txs.size() ? "," : "") << "\n";
    }
    std::cout << "]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: binder_tracer <path_to_transaction_log>\n";
        return 1;
    }

    std::vector<BinderTransaction> transactions;
    parse_log(argv[1], transactions);
    output_json(transactions);

    return 0;
}
