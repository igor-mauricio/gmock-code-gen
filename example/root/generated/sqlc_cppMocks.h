/* This code was generated. DO NOT EDIT */

#include <generated/sqlc_cpp.h>
#include <gmock/gmock.h>

namespace repo { 
    class MockRepository : public Repository {
    public:
        MOCK_METHOD(void, open, (std::string filename), (override));
        MOCK_METHOD(std::vector<getReplyIdsParams>, getReplyIds, (int parent_id), (override));
        MOCK_METHOD(std::vector<getAllPostsParams>, getAllPosts, (), (override));
        MOCK_METHOD(void, updatePost, (std::string title, std::string content, int id), (override));
        MOCK_METHOD(void, createPost, (std::string title, std::string content, std::optional<int> parent_id), (override));
        MOCK_METHOD(std::vector<getImagesParams>, getImages, (), (override));
        MOCK_METHOD(void, createImage, (std::string title, std::optional<std::vector<uint8_t>> content), (override));
        
    };
}
