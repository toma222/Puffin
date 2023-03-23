
#pragma once

#include <iostream>
#include <random>
#include <limits>
#include <memory>

#define PUFFIN_ID unsigned long long

namespace puffin
{
    class IDGenerator
    {
    private:
        std::random_device rd;
        std::mt19937_64 eng;
        std::uniform_int_distribution<PUFFIN_ID> distr;

        IDGenerator() : eng(rd())
        {
            return;
        }

    public:
        static IDGenerator s_generator;

        IDGenerator(const IDGenerator &) = delete;

        PUFFIN_ID GetRandomID()
        {
            return distr(eng);
        }

        static IDGenerator &Get()
        {
            return s_generator;
        }
    };

    // T is the type that is returned
    template <typename T>
    class IDHashTable
    {
    private:
        struct TableEntry
        {
            T m_entry;
            PUFFIN_ID m_key;
        };

        std::vector<TableEntry> table;

    public:
        PUFFIN_ID AddEntry(T entry)
        {
            TableEntry e;
            e.m_entry = entry;
            e.m_key = IDGenerator::Get().GetRandomID();
            table.push_back(e);

            return e.m_key;
        }

        T GetEntry(PUFFIN_ID id)
        {
            for (auto &&entry : table)
            {
                if (entry.m_key == id)
                {
                    return entry.m_entry;
                }
            }

            return NULL;
        }
    };
} // namespace puffin
