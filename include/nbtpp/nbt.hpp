#ifndef NBT_HPP_
#define NBT_HPP_

#include <iostream>
#include "tag.hpp"
#include "stde/streams/data.hpp"

namespace nbtpp {

    /**
     * Class to load NBT data
     */
    class nbt {

    public:
        enum compression : uint8_t {
            gzip = 1, zlib = 2, uncompressed = 3
        };

        /**
         * Create a blank NBT.
         */
        nbt() : m_tag(nullptr) {
        }

        /**
         * Loads NBT data from a file, detecting its compression (gzip'd or uncompressed) and setting the compressed flag accordingly.
         * @param in    File to load from
         */
        nbt(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream and sets the compressed flag to false.
         * @param in    Stream to load from.
         */
        nbt(std::istream& in);

        /**
         * Destructor
         */
        virtual ~nbt();

        /**
         * Loads NBT data from a file, detecting its compression (gzip'd or uncompressed) and setting the compressed flag accordingly.
         * @param in    File to load from
         */
        void load(std::ifstream& in);

        /**
         * Loads uncompressed data from a stream
         * @param in    Stream to load from.
         */
        void load(std::istream& in);

        void save(std::ostream& out);

        inline tag* getTag() const {
            return m_tag;
        }

        void debug();

        /**
         * Get the compression method used for the NBT data
         * @return
         */
        inline compression getCompressionMethod() const {
            return m_compression;
        }

        /**
         * Set the NBT compression method
         *
         * @param type
         */
        void setCompressionMethod(compression type = uncompressed) {
            m_compression = type;
        }

    private:
        void debug(const tag* data, int indent);
        tag* load_internal(stde::streams::data_istream& di, tag_type force_type = tag_type::TAG_Undef);

        tag *m_tag;
        compression m_compression = uncompressed;
    };

} /* namespace nbtpp */

#endif /* NBT_HPP_ */
