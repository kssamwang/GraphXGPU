//
// Created by Thoh Testarossa on 2019-08-08.
//

#include "ConnectedComponent.h"

#include <iostream>
#include <ctime>

template <typename VertexValueType, typename MessageValueType>
ConnectedComponent<VertexValueType, MessageValueType>::ConnectedComponent()
{

}

template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::InitGraph_array(VertexValueType *vValues, Vertex *vSet, Edge *eSet, int vCount)
{

}


template<typename VertexValueType, typename MessageValueType>
int ConnectedComponent<VertexValueType, MessageValueType>::MSGApply(Graph<VertexValueType> &g, const std::vector<int> &initVSet,
                                                   std::set<int> &activeVertice,
                                                   const MessageSet<MessageValueType> &mSet)
{
    //Availability check
    if(g.vCount <= 0) return 0;

    auto *mValues = new MessageValueType[g.vCount];
    for(int i = 0; i < g.vCount; i++) mValues[i] = INVALID_MASSAGE;
    for(const auto &m : mSet.mSet) mValues[m.dst] = m.value;

    this->MSGApply_array(g.vCount, g.eCount, &g.vList[0], 0, nullptr, &g.verticesValue[0], mValues);

    activeVertice.clear();
    for(const auto &v : g.vList)
    {
        if(v.isActive)
            activeVertice.insert(v.vertexID);
    }

    return activeVertice.size();
}

template<typename VertexValueType, typename MessageValueType>
int ConnectedComponent<VertexValueType, MessageValueType>::MSGGenMerge(const Graph<VertexValueType> &g, const std::vector<int> &initVSet,
                                                      const std::set<int> &activeVertice,
                                                      MessageSet<MessageValueType> &mSet)
{
    //Availability check
    if(g.vCount <= 0) return 0;

    auto *mValues = new MessageValueType[g.vCount];

    this->MSGGenMerge_array(g.vCount, g.eCount, &g.vList[0], &g.eList[0], 0, nullptr, &g.verticesValue[0], mValues);

    //Package mValues into result mSet
    for(int i = 0; i < g.vCount; i++)
    {
        if(mValues[i] != (MessageValueType)INVALID_MASSAGE)
            mSet.insertMsg(Message<VertexValueType>(INVALID_INITV_INDEX, i, mValues[i]));
    }

    return mSet.mSet.size();
}

template<typename VertexValueType, typename MessageValueType>
int ConnectedComponent<VertexValueType, MessageValueType>::MSGApply_array(int vCount, int eCount, Vertex *vSet, int numOfInitV,
                                                         const int *initVSet, VertexValueType *vValues,
                                                         MessageValueType *mValues)
{
    int avCount = 0;

    //Activity reset
    for(int i = 0; i < vCount; i++) vSet[i].isActive = false;

    //vValue apply
    for(int i = 0; i < vCount; i++)
    {
        if(vValues[i] > mValues[i])
        {
            vValues[i] = mValues[i];
            if(!vSet[i].isActive)
            {
                vSet[i].isActive = true;
                avCount++;
            }
        }
    }

    return avCount;
}

template<typename VertexValueType, typename MessageValueType>
int
ConnectedComponent<VertexValueType, MessageValueType>::MSGGenMerge_array(int vCount, int eCount, const Vertex *vSet, const Edge *eSet,
                                                       int numOfInitV, const int *initVSet,
                                                       const VertexValueType *vValues, MessageValueType *mValues)
{
    for(int i = 0; i < vCount; i++) mValues[i] = (MessageValueType)INVALID_MASSAGE;

    for(int i = 0; i < eCount; i++)
    {
        if(vSet[eSet[i].src].isActive)
        {
            if(mValues[eSet[i].dst] > vValues[eSet[i].src])
                mValues[eSet[i].dst] = vValues[eSet[i].src];
        }

        if(vSet[eSet[i].dst].isActive)
        {
            if(mValues[eSet[i].src] > vValues[eSet[i].dst])
                mValues[eSet[i].src] = vValues[eSet[i].dst];
        }
    }

    return vCount;
}

template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::MergeGraph(Graph<VertexValueType> &g,
                                                     const std::vector<Graph<VertexValueType>> &subGSet,
                                                     std::set<int> &activeVertices,
                                                     const std::vector<std::set<int>> &activeVerticeSet,
                                                     const std::vector<int> &initVList)
{
    //Init
    activeVertices.clear();
    for(auto &v : g.vList) v.isActive = false;

    for(const auto &subG : subGSet)
    {
        //vSet merge
        for(int i = 0; i < subG.vCount; i++)
            g.vList.at(i).isActive |= subG.vList.at(i).isActive;

        //vValues merge
        for(int i = 0; i < subG.vCount; i++)
        {
            if(g.verticesValue.at(i) > subG.verticesValue.at(i))
                g.verticesValue.at(i) = subG.verticesValue.at(i);
        }
    }

    for(const auto &AVs : activeVerticeSet)
    {
        for(auto av : AVs)
            activeVertices.insert(av);
    }
}

template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::Init(int vCount, int eCount, int numOfInitV)
{
    this->totalVValuesCount = vCount;
    this->totalMValuesCount = vCount;
}

template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::GraphInit(Graph<VertexValueType> &g, std::set<int> &activeVertices,
                                                    const std::vector<int> &initVList)
{
    //v init
    for(auto &v : g.vList)
    {
        v.isActive = true;
        activeVertices.insert(v.vertexID);
    }

    //vValues init
    g.verticesValue.reserve(g.vCount);
    g.verticesValue.assign(g.vCount, -1);
    for(int i = 0; i < g.vCount; i++) g.verticesValue.at(i) = (VertexValueType)i;
}


template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::Deploy(int vCount, int eCount, int numOfInitV)
{

}

template <typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::Free()
{

}

template<typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::ApplyStep(Graph<VertexValueType> &g, const std::vector<int> &initVSet,
                                                    std::set<int> &activeVertices)
{
    auto mGenSet = MessageSet<MessageValueType>();
    auto mMergedSet = MessageSet<MessageValueType>();

    mMergedSet.mSet.clear();
    MSGGenMerge(g, initVSet, activeVertices, mMergedSet);

    //Test
    std::cout << "MGenMerge:" << clock() << std::endl;
    //Test end

    activeVertices.clear();
    MSGApply(g, initVSet, activeVertices, mMergedSet);

    //Test
    std::cout << "Apply:" << clock() << std::endl;
    //Test end
}

template<typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::Apply(Graph<VertexValueType> &g, const std::vector<int> &initVList)
{
    //Init the Graph
    std::set<int> activeVertices = std::set<int>();
    auto mGenSet = MessageSet<MessageValueType>();
    auto mMergedSet = MessageSet<MessageValueType>();

    Init(g.vCount, g.eCount, initVList.size());

    GraphInit(g, activeVertices, initVList);

    Deploy(g.vCount, g.eCount, initVList.size());

    while(activeVertices.size() > 0)
        ApplyStep(g, initVList, activeVertices);

    Free();
}

template<typename VertexValueType, typename MessageValueType>
void ConnectedComponent<VertexValueType, MessageValueType>::ApplyD(Graph<VertexValueType> &g, const std::vector<int> &initVList,
                                                 int partitionCount)
{
    //Init the Graph
    std::set<int> activeVertices = std::set<int>();

    std::vector<std::set<int>> AVSet = std::vector<std::set<int>>();
    for(int i = 0; i < partitionCount; i++) AVSet.push_back(std::set<int>());
    std::vector<MessageSet<MessageValueType>> mGenSetSet = std::vector<MessageSet<MessageValueType>>();
    for(int i = 0; i < partitionCount; i++) mGenSetSet.push_back(MessageSet<MessageValueType>());
    std::vector<MessageSet<MessageValueType>> mMergedSetSet = std::vector<MessageSet<MessageValueType>>();
    for(int i = 0; i < partitionCount; i++) mMergedSetSet.push_back(MessageSet<MessageValueType>());

    Init(g.vCount, g.eCount, initVList.size());

    GraphInit(g, activeVertices, initVList);

    //Test
    //std::cout << 1 << std::endl;

    Deploy(g.vCount, g.eCount, initVList.size());

    int iterCount = 0;

    while(activeVertices.size() > 0)
    {
        //Test
        std::cout << ++iterCount << ":" << clock() << std::endl;
        //Test end

        auto subGraphSet = this->DivideGraphByEdge(g, partitionCount);

        for(int i = 0; i < partitionCount; i++)
        {
            AVSet.at(i).clear();
            AVSet.at(i) = activeVertices;
        }

        //Test
        std::cout << "GDivide:" << clock() << std::endl;
        //Test end

        for(int i = 0; i < partitionCount; i++)
            ApplyStep(subGraphSet.at(i), initVList, AVSet.at(i));

        activeVertices.clear();
        MergeGraph(g, subGraphSet, activeVertices, AVSet, initVList);
        //Test
        std::cout << "GMerge:" << clock() << std::endl;
        //Test end
    }

    Free();

    //Test
    std::cout << "end" << ":" << clock() << std::endl;
    //Test end
}
