#ifndef TAGS_COMPOUND_HPP_
#define TAGS_COMPOUND_HPP_

#include <vector>

#include "../tag.hpp"

namespace nbtpp::tags {
    class tag_compound: public tag {
    public:
        tag_compound(std::string name) : tag(name, type::TAG_Compound) {

        }

        virtual ~tag_compound() {
            for(tag* t : m_content) {
                delete t;
            }
        }

        void insert(tag* t) {
            m_content.push_back(t);
        }

        inline const std::vector<tag*>& getContent() const {
            return m_content;
        }
    private:
        std::vector<tag*> m_content;
    };
} /* namespace nbtpp::tags */

#endif /* TAGS_COMPOUND_HPP_ */
