#include <gtest/gtest.h>
#include "chat.pb.h"

TEST(ProtobufTest, SerializeDeserialize) {
    chat::ChatMessage msg;
    msg.set_cmd(chat::MESSAGE);
    msg.set_username("A");
    msg.set_content("Hello");

    std::string data;
    msg.SerializeToString(&data);

    chat::ChatMessage parsed;
    parsed.ParseFromString(data);

    EXPECT_EQ(parsed.username(), "A");
    EXPECT_EQ(parsed.content(), "Hello");
    EXPECT_EQ(parsed.cmd(), chat::MESSAGE);
}

TEST(ProtobufTest, InvalidData) {
    chat::ChatMessage msg;

    std::string garbage = "random_data";

    bool ok = msg.ParseFromString(garbage);

    EXPECT_FALSE(ok);
}

