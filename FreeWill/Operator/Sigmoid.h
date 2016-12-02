#ifndef SIGMOID_H
#define SIGMOID_H

#include "Operator.h"
#include "../DeviceSelection.h"
#include <cmath>

namespace FreeWill
{

    template<DeviceType DeviceUsed = CPU, typename DataType = float>
    class Sigmoid : public Operator<DeviceUsed>
    {
    public:
        Sigmoid()
            :Operator<DeviceUsed>({"Input"}, {"Output"}),
            m_input(nullptr),
            m_output(nullptr)
        {}  

        bool init() override
        {
            if (!m_input || !m_output)
            {
                return false;
            }

            if (m_input->shape() != m_output->shape())
            {
                return false;
            }

            return true;
        }

        void evaluate() override
        {
            if constexpr ((DeviceUsed & (CPU_SIMD | CPU_NAIVE)) != 0)
            {
                unsigned int size = m_input->shape().size();

                for(size_t i = 0; i < size; ++i)
                {
                    (*m_output)[i] = 1 / (1 + exp(-(*m_input)[i]));
                }
            }
        }

        void setInput(Tensor< DeviceUsed, DataType> *input)
        {
            m_input = input;
        }

        void setOutput(Tensor< DeviceUsed, DataType> *output)
        {
            m_output = output;
        }   
    private:
        Tensor<DeviceUsed, DataType> *m_input;
        Tensor<DeviceUsed, DataType> *m_output;   
    };

}
#endif
