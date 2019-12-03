#ifndef ANTNODE_H
#define ANTNODE_H

class AntNode
{
    public:
        /** Default constructor */
        AntNode();
        AntNode(unsigned int procId);
        /** Default destructor */
        virtual ~AntNode();

        int assignFeromon(int f) { return m_AntiFeromon = -f; };
        int vapeFeromon(unsigned int cycle);

    protected:

    private:
        unsigned int m_ProcessorId;
        int m_AntiFeromon;
        unsigned int m_FeromonTime;
};

#endif // ANTNODE_H
