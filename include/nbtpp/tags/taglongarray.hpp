#ifndef NBTPP_TAGS_TAGLONGARRAY_HPP_
#define NBTPP_TAGS_TAGLONGARRAY_HPP_

#include "../tag.hpp"
#include <vector>

namespace nbtpp {
    namespace tags {

        class tag_longarray: public tag {
        public:
            tag_longarray(std::string name) : tag(name, tag_type::TAG_Long_Array), m_value() {

            }

            virtual ~tag_longarray() {

            }

            void append(int64_t val) {
                m_value.push_back(val);
            }

            inline const std::vector<int64_t>& value() const {
                return m_value;
            }
        private:
            std::vector<int64_t> m_value;
        };

    }
}

#endif
