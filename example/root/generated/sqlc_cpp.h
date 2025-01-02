/* THIS FILE IS GENERATED BY SQLC. DO NOT EDIT. */

#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstdint>

#define FORMAT_SPIFFS_IF_FAILED true

namespace repo {
/* type definitions */
typedef int getReplyIdsParams;

typedef struct {
    int id;
    std::string title;
    std::string content;
    std::optional<int> parent_id;
} getAllPostsParams;

typedef struct {
    int id;
    std::string title;
    std::optional<std::vector<uint8_t>> content;
    std::optional<std::string> gender;
} getImagesParams;

class Repository {
public:

    int err = 0;
    virtual ~Repository() = default;
    virtual void open(std::string filename) = 0;
    virtual std::vector<getReplyIdsParams> getReplyIds(int parent_id) = 0;
	virtual std::vector<getAllPostsParams> getAllPosts() = 0;
	virtual void updatePost(
        std::string title,
        std::string content,
        int id
	) = 0;
	virtual void createPost(
        std::string title,
        std::string content,
        std::optional<int> parent_id
	) = 0;
	virtual std::vector<getImagesParams> getImages() = 0;
	virtual void createImage(
        std::string title,
        std::optional<std::vector<uint8_t>> content
	) = 0;

};

class SqliteRepository: public Repository {
private:
    void* database = nullptr;
public:

    void open(std::string filename);
    std::vector<getReplyIdsParams> getReplyIds(int parent_id);
	std::vector<getAllPostsParams> getAllPosts();
	void updatePost(
        std::string title,
        std::string content,
        int id
	);
	void createPost(
        std::string title,
        std::string content,
        std::optional<int> parent_id
	);
	std::vector<getImagesParams> getImages();
	void createImage(
        std::string title,
        std::optional<std::vector<uint8_t>> content
	);

};

}