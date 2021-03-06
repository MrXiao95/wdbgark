/*
    * WinDBG Anti-RootKit extension
    * Copyright � 2013-2018  Vyacheslav Rusakoff
    * 
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    * 
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.

    * This work is licensed under the terms of the GNU GPL, version 3.  See
    * the COPYING file in the top-level directory.
*/

//////////////////////////////////////////////////////////////////////////
//  Include this after "#define EXT_CLASS WDbgArk" only
//////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <engextcpp.hpp>

#include <string>
#include <vector>
#include <memory>

#include "symcache.hpp"
#include "dummypdb.hpp"
#include "processhlp.hpp"

namespace wa {

class WDbgArkProcess {
 public:
    explicit WDbgArkProcess(const std::shared_ptr<WDbgArkSymCache> &sym_cache,
                            const std::shared_ptr<WDbgArkDummyPdb> &dummy_pdb);

    WDbgArkProcess() = delete;

    bool IsInited(void) const { return m_inited; }
    const auto& GetProcessList() const { return m_process_list; }

    WDbgArkRemoteTypedProcess FindProcessByImageFileName(const std::string &process_name);
    WDbgArkRemoteTypedProcess FindProcessAnyGUIProcess();
    WDbgArkRemoteTypedProcess FindProcessAnyApiSetMap();

 private:
    bool FindProcessByImageFileName(const std::string &process_name, WDbgArkRemoteTypedProcess* process);

 private:
    using ProcessList = std::vector<WDbgArkRemoteTypedProcess>;

    bool m_inited = false;
    ProcessList m_process_list{};
    std::shared_ptr<WDbgArkSymCache> m_sym_cache{ nullptr };
    std::shared_ptr<WDbgArkDummyPdb> m_dummy_pdb{ nullptr };
};

}   // namespace wa

#endif  // PROCESS_HPP_
