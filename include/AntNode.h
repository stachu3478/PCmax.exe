#ifndef ANTNODE_H
#define ANTNODE_H

class AntNode
{
    public:
        /** Default constructor */
        AntNode();
        AntNode(int nodes, int time);
        /** Default destructor */
        virtual ~AntNode();

        AntNode pickRandom();
        int assignFeromon(int a, int i);
        int vapeFeromon(int a, int i);

    protected:

    private:
        int m_feromon;
        int m_feromonTime;
        int m_maxFeromonNode;
};

#endif // ANTNODE_H
