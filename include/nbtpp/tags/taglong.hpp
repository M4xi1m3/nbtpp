#ifndef NBTPP_TAGS_TAGLONG_HPP_
#define NBTPP_TAGS_TAGLONG_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {

        class tag_long: public tag {
        public:
            tag_long(std::string name, int64_t value) : tag(name, tag_type::TAG_Long), m_value(value) {

            }
            virtual ~tag_long() {

            }

            inline const int64_t value() const {
                return m_value;
            }

            void value(int64_t mValue) {
                m_value = mValue;
            }
        private:
            int64_t m_value;
        };

    }
}

#endif
