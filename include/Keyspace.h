#ifndef ADAK_KEYING_KEYSPACE_H
#define ADAK_KEYING_KEYSPACE_H

#include <stdint.h>

/*
    If this typedefed value is expanded to a value with greater precision
    (e.g: std bit array) ensure that all arithmetic operators are properly defined:
    
    e.g: +, -, *, /, << (rshift), >> (lshift), =, ==, etc.

    Also. ensure that the protobuf schema in message.proto
    is modified to store the correspondimg type (currently uint64)
*/
typedef std::uint64_t ADAK_Key_t;

class KeyspaceException : public std::runtime_error {
public:
    KeyspaceException(char const* const message) throw()
        : std::runtime_error(message), msg(message)
    {}
    
    const char* what() const throw() {
        return msg.c_str();
    }
    
private:
    std::string msg;
};

class Keyspace {
private:
    /**
     * Each keyspace block is designated by S-E/B, start is the S, end is the E, and suffix is B
     */
    ADAK_Key_t start;
    ADAK_Key_t end;
    uint32_t suffix;
public:
    Keyspace(unsigned long start, unsigned long end, unsigned long suffix);

    Keyspace(const Keyspace &obj);
    ~Keyspace() = default;
    
    /**
     * Uses one the key based on the available keyspace block and moves the start variable to the next position.
     * This allows the option to call getNextAvailableKey over and over to use up the keyspace
     * @return Next available 32 bit key
     */
    ADAK_Key_t getNextAvailableKey();

    ADAK_Key_t getSize();

    /**
     * This returns the same information that getNextAvailableKey does, but it doens't actually use up they keyspace.
     * This is for implementing the ADAK algorithm specification: Find the lowest-numbered starting
     * number S in the list of blocks/subblocks assigned to the node for the given database table.
     * @return
     */
    // ADAK_Key_t checkNextAvailableKey();

    // Getters
    ADAK_Key_t getStart() const { return this->start; }
    ADAK_Key_t getEnd() const { return this->end; }
    ADAK_Key_t getSuffix() const { return this->suffix; }
    
    constexpr inline bool isKeyAvailable() const {
        return start < end;
    }
};
#endif //ADAK_KEYING_KEYSPACE_H
