/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#include "cmMSVC60LinkLineComputer.h"

#include "cmSystemTools.h"

cmMSVC60LinkLineComputer::cmMSVC60LinkLineComputer(cmState::Directory stateDir)
  : cmLinkLineComputer(stateDir)
{
}

std::string cmMSVC60LinkLineComputer::ConvertToLinkReference(
  std::string const& lib) const
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  // Work-ardound command line parsing limitations in MSVC 6.0
  // Search for the last space.
  std::string::size_type pos = lib.rfind(' ');
  if (pos != lib.npos) {
    // Find the slash after the last space, if any.
    pos = lib.find('/', pos);

    // Convert the portion of the path with a space to a short path.
    std::string sp;
    if (cmSystemTools::GetShortPath(lib.substr(0, pos).c_str(), sp)) {
      // Append the rest of the path with no space.
      sp += lib.substr(pos);
      return sp;
    }
  }
#endif

  return cmLinkLineComputer::ConvertToLinkReference(lib);
}
