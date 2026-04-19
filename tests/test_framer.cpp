#include <gtest/gtest.h>
#include "../src/common/message_framer.h"

TEST(FramerTest, PackUnpackBasic) {
    std::vector<uint8_t> buffer;

    auto packed = MessageFramer::pack("hello");
    buffer.insert(buffer.end(), packed.begin(), packed.end());

    std::string out;
    bool ok = MessageFramer::unpack(buffer, out);

    EXPECT_TRUE(ok);
    EXPECT_EQ(out, "hello");
}

TEST(FramerTest, MultipleMessages) {
    std::vector<uint8_t> buffer;

    auto d1 = MessageFramer::pack("A");
    auto d2 = MessageFramer::pack("B");

    buffer.insert(buffer.end(), d1.begin(), d1.end());
    buffer.insert(buffer.end(), d2.begin(), d2.end());

    std::string out;

    EXPECT_TRUE(MessageFramer::unpack(buffer, out));
    EXPECT_EQ(out, "A");

    EXPECT_TRUE(MessageFramer::unpack(buffer, out));
    EXPECT_EQ(out, "B");
}

TEST(FramerTest, PartialMessage) {
    auto full = MessageFramer::pack("hello");

    std::vector<uint8_t> buffer;

    // chỉ insert 1 phần
    buffer.insert(buffer.end(), full.begin(), full.begin() + 3);

    std::string out;
    EXPECT_FALSE(MessageFramer::unpack(buffer, out));

    // insert phần còn lại
    buffer.insert(buffer.end(), full.begin() + 3, full.end());

    EXPECT_TRUE(MessageFramer::unpack(buffer, out));
    EXPECT_EQ(out, "hello");
}
