#ifndef TAGS_END_HPP_
#define TAGS_END_HPP_

#include "../tag.hpp"

namespace nbtpp {
    namespace tags {
        class tag_end: public tag {
        public:
            tag_end() : tag("", tag_type::TAG_End) {
            }
            virtual ~tag_end() {
            }
        };
    }
}

#endif
