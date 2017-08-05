#include "XMLParser.h"

network::network()
{

}

network::~network()
{

}

XMLParse::XMLParse()
{

}


XMLParse::~XMLParse()
{

}

//custom parser for XML data
void XMLParse::parseXML(const std::string &_filename)
{
    m_nodeRef = 0;
    m_wayRef = 0;
    Network.nodes.clear();
    Network.ways.clear();
    NewNetwork.nodes.clear();
    NewNetwork.ways.clear();
    // Open XML file
    std::fstream fileIn;
    fileIn.open( _filename.c_str(), std::ios::in );

    if( !fileIn.is_open() )
    {
        std::cerr<<"Could not open "<<_filename<<"\n";
        exit( EXIT_FAILURE );
    }

    // Define what separates words
    boost::char_separator<char> sep( " =\"" );
    std::string lineBuffer;
    bool inWay = false;
    bool storeWay = false;
    unsigned int lineNum = 0;
    unsigned int errLineNum = 0;

    while( !fileIn.eof() )
    {
        // Get a line and turn it into tokens
        getline( fileIn, lineBuffer, '\n' );
        ++lineNum;

        if( lineBuffer.size() != 0 )
        {
            tokenizer tokens( lineBuffer, sep );

            // Iterate through looking for nodes
            for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
            {
                //define boundries
                if( *tok_iter == "  " )
                {
                    tok_iter++;
                }
                else if( *tok_iter == "minlat" )
                {
                    m_minLat = boost::lexical_cast<float>( *++tok_iter );
                }
                else if( *tok_iter == "maxlat" )
                {
                    m_maxLat = boost::lexical_cast<float>( *++tok_iter );
                }
                else if( *tok_iter == "minlon" )
                {
                    m_minLon = boost::lexical_cast<float>( *++tok_iter );
                }
                else if( *tok_iter == "maxlon" )
                {
                    m_maxLon = boost::lexical_cast<float>( *++tok_iter );
                }
                // look for this token to create node id, as id token is used elsewhere in the XML
                // iterate tokens twice instead
                else if( *tok_iter == "<node" )
                {
                    std::stringstream ss;
                    if( *++tok_iter == "id")
                    {
                        ss << *++tok_iter;
                        ss >> Network.currentNode.nodeID;
                        ss >> NewNetwork.currentNode.nodeID;
                    }
                }
                // Look for latitude and longitude values
                else if( *tok_iter == "lat" )
                {
                    ++tok_iter;
                    Network.currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
                    NewNetwork.currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
                }
                else if( *tok_iter == "lon" )
                {
                    ++tok_iter;
                    Network.currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
                    Network.currentNode.nodeRef=m_nodeRef;
                    NewNetwork.currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
                    NewNetwork.currentNode.nodeRef=m_nodeRef;

                    Network.nodes.push_back(Network.currentNode);
                    NewNetwork.nodes.push_back(NewNetwork.currentNode);
                    ++m_nodeRef;
                }

                else if( *tok_iter == "<way" )
                {
                    if( inWay == true )
                    {
                        std::cerr<<"Warning: A way was opened without being closed. Unclosed way at line: "<<errLineNum<<"\n";
                    }
                    errLineNum = lineNum;
                    inWay = true;
                }

                else if( *tok_iter == "id" && inWay ==true )
                {
                    std::stringstream ss;
                    ss << *++tok_iter;
                    ss >> Network.currentWay.wayID;
                    ss >> NewNetwork.currentWay.wayID;
                }

                else if( *tok_iter == "ref" && inWay == true )
                {
                    std::stringstream ss;
                    uint64_t temp;
                    ss << *++tok_iter;
                    ss >> temp;
                    for(unsigned int i = 0; i < m_nodeRef; i++)
                    {
                        if(Network.nodes[i].nodeID == temp)
                        {
                            Network.currentWay.nodesInWay.push_back( Network.nodes[i] );
                            NewNetwork.currentWay.nodesInWay.push_back( NewNetwork.nodes[i] );
                            break;
                        }
                    }
                }

                else if( *tok_iter == "name" && inWay == true )
                {
                    std::stringstream ss;
                    while( *++tok_iter != "/>" )
                    {
                        if(*tok_iter != "v")
                        {
                          ss << *tok_iter;
                        }
                    }
                    ss >> Network.currentWay.name;
                    ss >> NewNetwork.currentWay.name;
                }
                else if ( *tok_iter == "highway" && inWay == true)
                {
                    storeWay = true;
                }
                else if ( *tok_iter == "</way>" && inWay == true )
                {
                    inWay = false;
                    if( storeWay == true )
                    {
                        unsigned int j;
                        Network.currentWay.wayRef = m_wayRef;
                        NewNetwork.currentWay.wayRef = m_wayRef;
                        // Building out a map of "next" nodes for each node in a way
                        // "next" is mapped to a corresponding way, in case a node is in more than one way
                        for(j = 1; j < Network.currentWay.nodesInWay.size(); j++)
                        {
                          Network.currentWay.nodesInWay[j - 1].next[Network.currentWay.wayRef] = &Network.currentWay.nodesInWay[j];
                          NewNetwork.currentWay.nodesInWay[j - 1].next[NewNetwork.currentWay.wayRef] = &NewNetwork.currentWay.nodesInWay[j];
                        }
                        // The final node in a way has a null next
                        Network.currentWay.nodesInWay[j - 1].next[Network.currentWay.wayRef] = nullptr;
                        Network.ways.push_back(Network.currentWay);

                        // The final node in a way has a null next
                        NewNetwork.currentWay.nodesInWay[j - 1].next[NewNetwork.currentWay.wayRef] = nullptr;
                        NewNetwork.ways.push_back(NewNetwork.currentWay);

                        m_wayRef++;
                    }
                    Network.currentWay.nodesInWay.clear();
                    Network.currentWay.name.clear();
                    NewNetwork.currentWay.nodesInWay.clear();
                    NewNetwork.currentWay.name.clear();
                    storeWay = false;
                }
            }
        }
    }

    std::cout<<"Number of ways: "<<m_wayRef<<"\n";
    std::cout<<"Number of nodes: "<<m_nodeRef<<"\n";

    // Close the file
    fileIn.close();
}

//check for unfinished nodes
void XMLParse::unfinishedNodes()
{
    for(unsigned int i = 0; i<Network.ways.size(); i++)
    {
        //only need to check first and last of a node, dont want to set all the nodes in between to unfinished
        if(Network.ways[i].nodesInWay[0].nodeLat>m_maxLat||Network.ways[i].nodesInWay[0].nodeLat<m_minLat||
           Network.ways[i].nodesInWay[0].nodeLon>m_maxLon||Network.ways[i].nodesInWay[0].nodeLon<m_minLon)
        {
            Network.ways[i].nodesInWay[0].isUnfinished=true;
            NewNetwork.ways[i].nodesInWay[0].isUnfinished=true;
        }
        else if(Network.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].nodeLat>m_maxLat||
                Network.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].nodeLat<m_minLat||
                Network.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].nodeLon>m_maxLon||
                Network.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].nodeLon<m_minLon)
        {
            Network.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].isUnfinished=true;
            NewNetwork.ways[i].nodesInWay[Network.ways[i].nodesInWay.size()-1].isUnfinished=true;
        }
    }
}

//store any node which current node intersects with, needed for geometry building
void XMLParse::checkIntersections()
{
    for(unsigned int i = 0; i<Network.ways.size(); i++)
    {
        for(unsigned int j = 0; j<Network.ways[i].nodesInWay.size(); j++)
        {
            for(unsigned int k = 0; k<Network.ways.size(); k++)
            {
                if(i == k)
                {
                    continue;
                }
                else
                {
                    for(unsigned int l = 0; l<Network.ways[k].nodesInWay.size(); l++)
                    {
                        if(Network.ways[i].nodesInWay[j].nodeID == Network.ways[k].nodesInWay[l].nodeID && Network.ways[i].nodesInWay[j].nodeRef != int(Network.nodes.size()))
                        {
                            Network.ways[i].nodesInWay[j].isIntersection = true;
                            Network.ways[i].nodesInWay[j].numIntersections++;
                            Network.ways[i].nodesInWay[j].intersectsWith.push_back(Network.ways[k].name);
                            Network.ways[i].intersections.push_back(Network.ways[i].nodesInWay[j]);

                            NewNetwork.ways[i].nodesInWay[j].isIntersection = true;
                            NewNetwork.ways[i].nodesInWay[j].numIntersections++;
                            NewNetwork.ways[i].nodesInWay[j].intersectsWith.push_back(NewNetwork.ways[k].name);
                            NewNetwork.ways[i].intersections.push_back(NewNetwork.ways[i].nodesInWay[j]);
                        }
                    }
                }
            }
        }
    }
}


