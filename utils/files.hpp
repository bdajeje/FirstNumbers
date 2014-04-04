#ifndef FILES_HPP
#define FILES_HPP

#include <boost/filesystem.hpp>

namespace utils {
namespace files {

/*! Read a file
 *  \param filepath to access the file
 *  \param result   [out] where to store content of the read file
 *  \return true if everything was ok, false otherwise
 *  \warning the content of the result will be override
 */
bool read( const std::string& filepath, std::string& result );

/*! Tests if a file exists
 *  \param filepath Complete path of the file to test
 *  \return True if a file with the given filepath exists
 */
inline bool exists(const std::string& filepath) { return boost::filesystem::exists(filepath); }

/*! Create a file with a given content
 *  \param filepath a the file to create
 *  \param content  to add to the file
 *  \param override if a file is already existing at the given location ovveride it or not
 *  \return true if the file has been successfully created
 */
bool create( const std::string& filepath, const std::string& content = "", bool override = false );

/*! Append some content at the end of a file
 *  \param filepath where to write
 *  \param content  to append to the file
 *  \return true if the content has successfuly been append, false otherwise
 */
bool append(const std::string& filepath, const std::string& content);

}
}

#endif // FILES_HPP
