#ifndef TAGS_COMPOUND_HPP_
#define TAGS_COMPOUND_HPP_

#include <vector>

#include "../tag.hpp"

namespace nbtpp::tags {
    class tag_compound: public tag {
    public:
        tag_compound(std::string name) : tag(name, tag_type::TAG_Compound) {

        }

        virtual ~tag_compound() {
            for (tag *t : m_content) {
                delete t;
            }
        }

        void insert(tag* t) {
            for (auto i = m_content.begin(); i < m_content.end(); i++) {
                if ((*i)->name() == t->name()) {
                    m_content.erase(i);
                    break;
                }
            }

            m_content.push_back(t);
        }

        tag* get(std::string name) const {
            for (auto i = m_content.begin(); i < m_content.end(); i++) {
                if ((*i)->name() == name) {
                    return *i;
                }
            }

            return nullptr;
        }

        bool exists(std::string name) const {
            for (auto i = m_content.begin(); i < m_content.end(); i++) {
                if ((*i)->name() == name) {
                    return true;
                }
            }

            return false;
        }

        tag* operator[](const std::string& name) const {
            return get(name);
        }

        inline const std::vector<tag*>& value() const {
            return m_content;
        }
    private:
        std::vector<tag*> m_content;
    };
} /* namespace nbtpp::tags */

#endif /* TAGS_COMPOUND_HPP_ */
