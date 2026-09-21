#ifndef YUZUENGIN_LIB_HPP
#define YUZUENGIN_LIB_HPP

#include <chrono>
#include <cstdint>
#include <vector>
#include <fstream>

#define unused(x) (void)(x)

namespace yLib
{
    namespace time
    {
        inline uint64_t getNanoSecondes()
        {
            auto tse = std::chrono::steady_clock::now().time_since_epoch();
            return std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
        }

        constexpr uint64_t OneBillion = 1'000'000'000;
    };

    namespace Serializer
    {
        class Writer;

        template <typename T>
        concept WriteSerializable = requires(T element, Serializer::Writer &serializer) {
            { element.write(serializer) } -> std::same_as<void>;
        };

        template <typename T>
        concept IsPrimitif = std::is_arithmetic_v<T> || std::is_enum_v<T>; // || std::_Is_character_or_bool<T>;

        class Writer
        {

        public:
            Writer(std::string filename, std::ios_base::openmode mode = std::ios::binary)
            {
                file = std::ofstream(filename, mode);
            }

            template <WriteSerializable T>
            void write(const T &element)
            {
                element.write(*this);
            }

            template <typename T>
            void write(const std::vector<T> &vector)
            {
                write(vector.size());
                for (const auto &e : vector)
                    write(e);
            }

            void write(const std::string &element)
            {
                write(element.size());
                file.write(element.data(), element.size());
            }

            template <IsPrimitif T>
            void write(const T &element)
            {
                file.write(reinterpret_cast<const char *>(&element), sizeof(element));
            }

        private:
            std::ofstream file;
        };

        class Reader;

        template <typename T>
        concept ReadSerializable = requires(T element, Serializer::Reader &serializer) {
            { element.read(serializer) } -> std::same_as<void>;
        };

        class Reader
        {

        public:
            Reader(std::string filename, std::ios_base::openmode mode = std::ios::binary)
            {
                file = std::ifstream(filename, mode);
            }

            template <ReadSerializable T>
            void read(T &element)
            {
                element.read(*this);
            }

            template <typename T>
            void read(std::vector<T> &vector)
            {
                size_t size;
                read(size);
                vector.resize(size);
                for (auto &e : vector)
                    read(e);
            }

            void read(std::string &element)
            {
                size_t size;
                read(size);
                element.resize(size);
                file.read(element.data(), size);
            }

            template <IsPrimitif T>
            void read(T &element)
            {
                file.read(reinterpret_cast<char *>(&element), sizeof(element));
            }

        private:
            std::ifstream file;
        };
    }

}

#endif