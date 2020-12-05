#ifndef TAGS_END_HPP_
#define TAGS_END_HPP_

#include "../tag.hpp"

namespace nbtpp::tags {
    class tag_end: public tag {
    public:
        tag_end() : tag("", type::TAG_End) {
        }
        virtual ~tag_end() {
        }
    };
} /* namespace nbtpp::tags */

#endif /* TAGS_END_HPP_ */
