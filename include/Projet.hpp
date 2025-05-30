#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>


#include "Generic_mapper.hpp"
#include "Generic_connection_parser.hpp"
using namespace travel;



namespace travel {

    class Projet : public Generic_mapper {
    public:
        std::vector<std::pair<uint64_t, uint64_t>> compute_travel(uint64_t _start, uint64_t _end) override;
        std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(uint64_t _start, uint64_t _end) override;

        std::vector<std::pair<uint64_t, uint64_t>> compute_travel(const std::string&, const std::string&) override;
        std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(const std::string& _start, const std::string& _end) override;
        std::vector<std::string> getAllStationNames() const;
        void read_connections(const std::string& _filename) override;
        void read_stations(const std::string& _filename) override;

    };
}
