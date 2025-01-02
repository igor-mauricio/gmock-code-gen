/* THIS FILE IS GENERATED BY SQLC. DO NOT EDIT. */

#include <sqlite3.h>
#include <cstring>
#include <SPIFFS.h>
#include <sqlc_cpp.h>

namespace repo {
    // sqlite3 *db = nullptr;

    sqlite3* toSqlite3(void* db) {
        return reinterpret_cast<sqlite3*>(db);
    }

    sqlite3** toSqlite3Ptr(void** db) {
        return reinterpret_cast<sqlite3**>(db);
    }

    void SqliteRepository::open(std::string filename) {
        if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
            Serial.println("Failed to mount file system");
            return;
        }
        SPIFFS.remove("/test1.db");

        sqlite3_initialize();
        err = sqlite3_open(filename.c_str(), toSqlite3Ptr(&this->database));
        if (err) {
            Serial.printf("Can't open database: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return;
        }
        Serial.println("Opened database successfully");

        std::string sql = "CREATE TABLE IF NOT EXISTS post ( id INTEGER PRIMARY KEY, title TEXT NOT NULL, content TEXT NOT NULL, parent_id INTEGER ); CREATE TABLE IF NOT EXISTS images ( id INTEGER PRIMARY KEY, title TEXT NOT NULL, content BLOB, gender CHAR(1) );";
        char *errmsg;
        err = sqlite3_exec(toSqlite3(this->database), sql.c_str(), nullptr, nullptr, &errmsg);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            Serial.printf("error message: %s\n", errmsg);
            Serial.printf("error code: %d\n", err);
            return;
        }
    }
    
    std::vector<getReplyIdsParams> SqliteRepository::getReplyIds(int parent_id){
        std::string sql = "SELECT id FROM post WHERE parent_id = ?";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return std::vector<getReplyIdsParams> {} ;
        }
		err = sqlite3_bind_int(stmt, 1, parent_id);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return std::vector<getReplyIdsParams> {} ;
        }
        std::vector<getReplyIdsParams> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
			getReplyIdsParams row;
            row = sqlite3_column_int(stmt, 0);
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
        return result;
	}

    std::vector<getAllPostsParams> SqliteRepository::getAllPosts(){
        std::string sql = "SELECT id, title, content, parent_id FROM post";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return std::vector<getAllPostsParams> {} ;
        }
        std::vector<getAllPostsParams> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
			getAllPostsParams row;
            row.id = sqlite3_column_int(stmt, 0);
            row.title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            row.content = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL) {
            row.parent_id = sqlite3_column_int(stmt, 3);
            }
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
        return result;
	}

    void SqliteRepository::updatePost(
        std::string title,
        std::string content,
        int id
	){
        std::string sql = "UPDATE post SET title = ?, content = ? WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return ;
        }
		err = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
		err = sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
		err = sqlite3_bind_int(stmt, 3, id);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
        err = sqlite3_step(stmt);
        if (err != SQLITE_DONE) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return;
        }
        sqlite3_finalize(stmt);
        err = 0;
	}

    void SqliteRepository::createPost(
        std::string title,
        std::string content,
        std::optional<int> parent_id
	){
        std::string sql = "INSERT INTO post (title, content, parent_id) VALUES (?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return ;
        }
		err = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
		err = sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
		err = sqlite3_bind_int(stmt, 3, parent_id);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
        err = sqlite3_step(stmt);
        if (err != SQLITE_DONE) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return;
        }
        sqlite3_finalize(stmt);
        err = 0;
	}

    std::vector<getImagesParams> SqliteRepository::getImages(){
        std::string sql = "SELECT id, title, content, gender FROM images";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return std::vector<getImagesParams> {} ;
        }
        std::vector<getImagesParams> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
			getImagesParams row;
            row.id = sqlite3_column_int(stmt, 0);
            row.title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            if (sqlite3_column_type(stmt, 2) != SQLITE_NULL) {
            const void* content_blob = sqlite3_column_blob(stmt, 2);
            int content_size = sqlite3_column_bytes(stmt, 2);
            row.content = std::vector<uint8_t>(content_size);
            if (content_blob && content_size > 0) {
                std::memcpy(row.content.data(), content_blob, content_size);
            }
            }
            if (sqlite3_column_type(stmt, 3) != SQLITE_NULL) {
            }
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
        return result;
	}

    void SqliteRepository::createImage(
        std::string title,
        std::optional<std::vector<uint8_t>> content
	){
        std::string sql = "INSERT INTO images (title, content) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        err = sqlite3_prepare_v2(toSqlite3(this->database), sql.c_str(), -1, &stmt, nullptr);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));

            return ;
        }
		err = sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
		err = sqlite3_bind_blob(stmt, 2, content.data(), content.size(), SQLITE_STATIC);
        if (err != SQLITE_OK) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return ;
        }
        err = sqlite3_step(stmt);
        if (err != SQLITE_DONE) {
            Serial.printf("SQL error: %s\n", sqlite3_errmsg(toSqlite3(this->database)));
            return;
        }
        sqlite3_finalize(stmt);
        err = 0;
	}

}
