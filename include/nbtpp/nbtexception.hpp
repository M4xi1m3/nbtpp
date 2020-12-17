#ifndef NBTPP_NBTEXCEPTION_HPP_
#define NBTPP_NBTEXCEPTION_HPP_

#include <exception>
#include <string>

namespace nbtpp {
    /**
     * NBT-Parsing exception
     */
    class nbt_exception: public std::exception {
    public:
        /**
         * Constructor
         *
         * @param message   Message associated with the exception.
         */
        nbt_exception(const std::string& message) : std::exception(), m_message(message) {
        }
        virtual const char* what() const noexcept {
            return m_message.c_str();
        }
    private:
        std::string m_message;
    };
}

#endif
