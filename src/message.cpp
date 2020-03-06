#include "message.hpp"

void addCollectionInfoRecord(InformationalMessageContents::CollectionInformationRecord *collection,
                             float createdDay, float createdWeek, float longAlloc, float shortAlloc) {
    auto *creationRateData = new InformationalMessageContents::CollectionInformationRecord::CreationRateData();
    creationRateData->set_createdpreviousday(createdDay);
    creationRateData->set_createdpreviousweek(createdWeek);
    creationRateData->set_longallocationratio(longAlloc);
    creationRateData->set_shortallocationratio(shortAlloc);
    collection->set_allocated_creationratedata(creationRateData);
}

Message newBaseMessage(const HexDigest &sendingUUID, const HexDigest &destUUID, uint32_t lastReceived,
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