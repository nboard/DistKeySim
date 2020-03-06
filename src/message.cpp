#include "message.hpp"

/**
 * Adds a collection information record to an informational message contents instance
 * @param collection Pointer to collection information instance
 * @param createdDay float Keys created per day over 24 hours: CS
 * @param createdWeek float indicating Keys created per day over 7 days: CL
 * @param longAlloc float indicating Long-term keyspace allocation ratio: AL
 * @param shortAlloc float indicating Short-term keyspace allocation ratio: AS
 */
void addCollectionInfoRecord(InformationalMessageContents::CollectionInformationRecord *collection,
                             float createdDay, float createdWeek, float longAlloc, float shortAlloc) {
    auto *creationRateData = new InformationalMessageContents::CollectionInformationRecord::CreationRateData();
    creationRateData->set_createdpreviousday(createdDay);
    creationRateData->set_createdpreviousweek(createdWeek);
    creationRateData->set_longallocationratio(longAlloc);
    creationRateData->set_shortallocationratio(shortAlloc);
    collection->set_allocated_creationratedata(creationRateData);
}

/** Generate new base protobuf message instance. Preferrably use newInformationalMessage or newKeyspaceMessage
 *
 * @param sendingUUID UUID string for node sending message
 * @param destUUID UUID string of destination, set to 00000000-0000-0000-0000-000000000000 if peer node ID not known
 * @param lastReceived Highest received consecutive Message ID from destination node (acknowledgment)
 * @param channelState Channel state (initial startup, normal communication, or channel shutdown)
 * @param msgID Local message ID (64 bit integer, starting at 1)
 * @param unixTimestamp Timestamp for message. Leaving default -1 will set timestamp to current system time
 * @throw std::invalid_argument if msgID is 0
 * @return Message instance created. Need to add message contents (either Keyspace or Informational) to have valid message
 */
Message newBaseMessage(HexDigest &sendingUUID, HexDigest &destUUID, uint32_t lastReceived,
                       Message::ChannelState channelState, uint64_t msgID, long unixTimestamp) {
    if (msgID == 0) {
        throw std::invalid_argument("msgID is zero");
    }
    
    Message msg;
    msg.set_sourcenodeid(sendingUUID);
    msg.set_destnodeid(destUUID);
    msg.set_lastreceivedmsg(lastReceived);
    msg.set_channelstate(channelState);
    
    // Set timestamp if value provided, otherwise set as current time
    // NOTE: Must use Timestamp pointer to avoid segfault - protobuf will handle freeing of pointers in messages
    auto *timestamp = new google::protobuf::Timestamp();
    if (unixTimestamp < 0) {
        unixTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
    timestamp->set_seconds(unixTimestamp);
    timestamp->set_nanos(0);
    msg.set_allocated_timestamp(timestamp);
    
    msg.set_messageid(msgID);
    
    return msg;
}

/** Add data to message instance to change it to valid informational message
 *
 * @param msg Unpopulated message instance to add informational records to
 * @param records Collection Information Records to be added to message
 */
void toInformationalMessage(Message &msg, std::initializer_list<CollectionInfoRecord> records) {
    // Indicate message type as information
    msg.set_messagetype(Message::MessageType::Message_MessageType_INFORMATION);
    
    // Add default empty message contents
    auto *infoContents = new InformationalMessageContents();
    for (CollectionInfoRecord record : records) {
        auto *collection = infoContents->add_records();
        collection->set_collectionname(record.name);
        addCollectionInfoRecord(collection, record.createdDay, record.createdWeek, record.longTermAllocation,
                                record.shortTermAllocation);
    }
    
    msg.set_allocated_info(infoContents);
}

/** Add data to message instance to change it to valid keyspace exchange message
 *
 * @param msg Unpopulated message instance to add keyspace exchange message to
 * @param records Keyspace exchange records to add to message
 */
void toKeyspaceMessage(Message &msg, std::initializer_list<KeyspaceExchangeRecord> records) {
    // Indicate message type as information
    msg.set_messagetype(Message::MessageType::Message_MessageType_KEYSPACE);
    
    // Add default empty message contents
    auto *contents = new KeyspaceMessageContents();
    for (KeyspaceExchangeRecord record : records) {
        auto *keyspace = contents->add_keyspaces();
        keyspace->set_name(record.name);
        keyspace->set_startid(record.startID);
        keyspace->set_endid(record.endID);
        keyspace->set_suffixbits(record.suffixBits);
    }
    
    msg.set_allocated_keyspace(contents);
}