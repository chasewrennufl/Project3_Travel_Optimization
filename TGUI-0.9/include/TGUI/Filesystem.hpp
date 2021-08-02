/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_FILESYSTEM_HPP
#define TGUI_FILESYSTEM_HPP

#include <TGUI/String.hpp>
#include <cstdint>
#include <vector>
#include <ctime>

#ifdef TGUI_USE_STD_FILESYSTEM
    #include <filesystem>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Helper functionality for filesystem access
    ///
    /// When TGUI is built with c++17 support then std::filesystem is used on newer compilers.
    /// Otherwise, POSIX or Windows-specific code is used to implement the functionality.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Filesystem
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Object to represent paths on a filesystem
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        class TGUI_API Path
        {
        public:

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Default constructor that creates an empty path object
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path() = default;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor that creates a Path object from the given path string
            ///
            /// @param path  The path to be parsed and stored in this object
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            explicit Path(const String& path);

#ifdef TGUI_USE_STD_FILESYSTEM
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor that creates a Path object from an std::filesystem::path object
            ///
            /// @param path  The path to be stored in this object
            ///
            /// This function uses a template parameter to prevent implicit conversions that cause ambiguous overload errors.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            template <typename PathType, std::enable_if_t<std::is_same_v<PathType, std::filesystem::path>, int> = 0>
            explicit Path(const PathType& path) :
                m_path(path)
            {
            }
#endif

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if this object is empty
            ///
            /// @return True when default-constructed or when set to an empty string, false otherwise
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool isEmpty() const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the path as a string
            ///
            /// @return The path stored in this object
            ///
            /// Slashes are always used as separator on any OS so that relative paths are portable.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            String asString() const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns to path to the parent directory.
            ///
            /// @return Parent directory
            ///
            /// If the path has a filename then the parent directory is the directory containing that file.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path getParentPath() const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns to filename component of the path (where the path consists of getParentPath() / getFilename())
            ///
            /// @return Filename component of the path
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            String getFilename() const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the lexically normal form of the path (path with '.' and '..' resolved)
            ///
            /// @return Normal form of the path, based on the text representation (no filesystem access is done)
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path getNormalForm() const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the path as a string, but with a string type and contents that depends on the OS
            ///
            /// @return The path stored in this object
            ///
            /// An std::wstring is returned on Windows with backslashes as separator.
            /// On other platforms, a UTF-8 encoded std::string is returned with slashes as separator.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TGUI_SYSTEM_WINDOWS
            std::wstring asNativeString() const;
#else
            std::string asNativeString() const;
#endif

#ifdef TGUI_USE_STD_FILESYSTEM
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the std::filesystem::path that this object used to store the data in
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            operator const std::filesystem::path&() const
            {
                return m_path;
            }
#endif

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns a new path that consists of this object joined with another path
            ///
            /// @param path  The path to join to this one
            ///
            /// @return The joined paths
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path operator/(const Path& path) const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns a new path that consists of this object joined with another path
            ///
            /// @param path  The path to join to this one
            ///
            /// @return The joined paths
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path operator/(const String& path) const
            {
                return *this / Path(path);
            }


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Joins this object with another path
            ///
            /// @param path  The path to join to this one
            ///
            /// @return Reference to this object
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path& operator/=(const Path& path);


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Joins this object with another path
            ///
            /// @param path  The path to join to this one
            ///
            /// @return Reference to this object
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            Path& operator/=(const String& path)
            {
                return *this /= Path(path);
            }


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Checks whether the paths are equal
            ///
            /// @param other  The path to compare with
            ///
            /// This function only checks whether the path strings are identical or not.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator==(const Path& other) const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Checks whether the paths are not equal
            ///
            /// @param other  The path to compare with
            ///
            /// This function only checks whether the path strings are identical or not.
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator!=(const Path& other) const;


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        private:

#ifdef TGUI_USE_STD_FILESYSTEM
            std::filesystem::path m_path;
#else
            std::vector<String> m_parts;
            String m_root; // Drive letter or empty
            bool m_absolute = false;
#endif
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Information about a file or directory, used to return data from the listFilesInDirectory function
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct TGUI_API FileInfo
        {
            String filename;
            Path path;
            bool directory = false; // Is it a regular file or a folder?
            std::uintmax_t fileSize = 0;
            std::time_t modificationTime = 0;
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a directory exists
        ///
        /// @param path  Path to the directory to check
        ///
        /// @return True if the directory exists, false otherwise
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool directoryExists(const Path& path);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a directory exists
        ///
        /// @param path  Path to the directory to check
        ///
        /// @return True if the directory exists, false otherwise
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool directoryExists(const String& path)
        {
            return directoryExists(Path{path});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a file exists
        ///
        /// @param path  Path to the file to check
        ///
        /// @return True if the file exists, false otherwise
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool fileExists(const Path& path);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a file exists
        ///
        /// @param path  Path to the file to check
        ///
        /// @return True if the file exists, false otherwise
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool fileExists(const String& path)
        {
            return fileExists(Path{path});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create a directory
        ///
        /// @param path  Path to the directory to create
        ///
        /// @return True if the directory was created or already existed, false on failure.
        ///
        /// This function will fail if the parent directory doesn't exist. It won't try to recursively create the directory.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool createDirectory(const Path& path);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create a directory
        ///
        /// @param path  Path to the directory to create
        ///
        /// @return True if the directory was created or already existed, false on failure.
        ///
        /// This function will fail if the parent directory doesn't exist. It won't try to recursively create the directory.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool createDirectory(const String& path)
        {
            return createDirectory(Path{path});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the home directory
        ///
        /// @return Path to the home directory
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Path getHomeDirectory();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current working directory
        ///
        /// @return Path to the current working directory
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Path getCurrentWorkingDirectory();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the directory to store application data
        ///
        /// @return Path to local app data directory
        ///
        /// On Windows, this returns the value of %LOCALAPPDATA%
        /// On macOS, this returns $HOME/Library/Application Support
        /// On Linux and other platforms, this returns $HOME/.local/share
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Path getLocalDataDirectory();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of all files and folders inside a given directory
        ///
        /// @param path  Path in which all directories and files should be listed
        ///
        /// @return List of files (including directories) that are found within the given path
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static std::vector<FileInfo> listFilesInDirectory(const Path& path);
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_FILESYSTEM_HPP
