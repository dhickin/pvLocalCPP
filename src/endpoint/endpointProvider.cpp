/*
 * Copyright information and license terms for this software can be
 * found in the file LICENSE that is included with the distribution
 */
/**
 * @author Dave Hickin
 * @date 2016.06
 */

#include <stdexcept>

#include <pv/sharedPtr.h>

#include <pv/endpointProvider.h>


#include <shareLib.h>

namespace epics {
namespace pvLocal {

bool NamedEndpointProvider::hasEndpoint(const std::string & name)
{
    return (m_endpoints.find(name) != m_endpoints.end());
} 


EndpointPtr NamedEndpointProvider::getEndpoint(const std::string & name)
{
    EndpointPtr endpoint;
    EndpointMap::const_iterator iter;
    {
        epics::pvData::Lock guard(mutex);
        iter = m_endpoints.find(name);
    }
    if (iter != m_endpoints.end())
        endpoint = iter->second;

    return endpoint;
}

void NamedEndpointProvider::registerEndpoint(const std::string & name, Endpoint::shared_pointer const & endpoint)
{
    epics::pvData::Lock guard(mutex);
    m_endpoints[name] = endpoint;
}

}
}

