/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <ht_platform.h>
#include <ht_string.h>
#include <ht_math.h>

#ifdef HT_SYS_LINUX
#include <cstring>
#endif

namespace Hatchit {

    namespace Resource {

        class IShader;

        class HT_API ShaderVariable 
        {
        public:
            virtual ~ShaderVariable() {
                if (m_data != nullptr)
                {
                    delete[] m_data;
                    m_data = nullptr;
                }
            };

            enum Type
            {
                INT,
                FLOAT,
                DOUBLE,
                FLOAT2,
                FLOAT3,
                FLOAT4,
                MAT4
            };

            inline Type GetType() { return m_type; }
            inline void* GetData() { return m_data; }

            static inline Type TypeFromString(const std::string& string) 
            {
                if (string == "INT")
                    return Type::INT;
                else if (string == "FLOAT")
                    return Type::FLOAT;
                else if (string == "DOUBLE")
                    return Type::DOUBLE;
                else if (string == "FLOAT2")
                    return Type::FLOAT2;
                else if (string == "FLOAT3")
                    return Type::FLOAT3;
                else if (string == "FLOAT4")
                    return Type::FLOAT4;
                else if (string == "MAT4")
                    return Type::MAT4;
                else
                {
                    HT_DEBUG_PRINTF("WARNING: UNKNOWN SHADER VARIABLE TYPE; RETURNING INT\n");
                    return Type::INT;
                }
            }

            static inline size_t SizeFromType(ShaderVariable::Type type)
            {
                size_t size = 0;

                switch (type)
                {
                case ShaderVariable::Type::INT:
                    size = sizeof(uint32_t);
                    break;
                case ShaderVariable::Type::DOUBLE:
                    size = sizeof(double);
                    break;
                case ShaderVariable::Type::FLOAT:
                    size = sizeof(float);
                    break;
                case ShaderVariable::Type::FLOAT2:
                    size = sizeof(float) * 2;
                    break;
                case ShaderVariable::Type::FLOAT3:
                    size = sizeof(float) * 3;
                    break;
                case ShaderVariable::Type::FLOAT4:
                    size = sizeof(float) * 4;
                    break;
                case ShaderVariable::Type::MAT4:
                    size = sizeof(float) * 16;
                    break;
                }
                
                return size;
            }

        protected:
            Type m_type;
            void* m_data = nullptr;
        };

        template<typename T>
        class HT_API ShaderVariableTemplate : public ShaderVariable
        {
        public:
            inline ShaderVariableTemplate();
            inline ShaderVariableTemplate(T t);
            
            inline void SetData(T t);
        };



        template<>
        inline void HT_API ShaderVariableTemplate<int>::SetData(int data)
        {
            memcpy(m_data, &data, sizeof(int));
        }

        template <>
        inline HT_API ShaderVariableTemplate<int>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(int)];
            SetData(0);
            m_type = Type::INT;
        }

        template <>
        inline HT_API ShaderVariableTemplate<int>::ShaderVariableTemplate(int data)
        {
            m_data = new BYTE[sizeof(int)];
            SetData(data);
            m_type = Type::INT;
        }



        template<>
        inline void HT_API ShaderVariableTemplate<float>::SetData(float data)
        {
            memcpy(m_data, &data, sizeof(float));
        }

        template <>
        inline HT_API ShaderVariableTemplate<float>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(float)];
            SetData(0.0f);
            m_type = Type::FLOAT;
        }

        template <>
        inline HT_API ShaderVariableTemplate<float>::ShaderVariableTemplate(float data)
        {
            m_data = new BYTE[sizeof(float)];
            SetData(data);
            m_type = Type::FLOAT;
        }
       


        template<>
        inline void HT_API ShaderVariableTemplate<double>::SetData(double data)
        {
            memcpy(m_data, &data, sizeof(double));
        }

        template <>
        inline HT_API ShaderVariableTemplate<double>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(double)];
            SetData(0.0);
            m_type = Type::DOUBLE;
        }

        template <>
        inline HT_API ShaderVariableTemplate<double>::ShaderVariableTemplate(double data)
        {
            m_data = new BYTE[sizeof(double)];
            SetData(data);
            m_type = Type::DOUBLE;
        }



        template<>
        inline void HT_API ShaderVariableTemplate<Math::Vector2>::SetData(Math::Vector2 data)
        {
            memcpy(m_data, data.m_data, sizeof(float) * 2);
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector2>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(float) * 2];
            SetData(Math::Vector2());
            m_type = Type::FLOAT2;
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector2>::ShaderVariableTemplate(Math::Vector2 data)
        {
            m_data = new BYTE[sizeof(float) * 2];
            SetData(data);
            m_type = Type::FLOAT2;
        }


	    template<>
        inline void HT_API ShaderVariableTemplate<Math::Vector3>::SetData(Math::Vector3 data)
        {
            memcpy(m_data, data.m_data, sizeof(float) * 3);
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector3>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(float) * 3];
            SetData(Math::Vector3());
            m_type = Type::FLOAT3;
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector3>::ShaderVariableTemplate(Math::Vector3 data)
        {
            m_data = new BYTE[sizeof(float) * 3];
            SetData(data);
            m_type = Type::FLOAT3;
        }       



        template<>
        inline void HT_API ShaderVariableTemplate<Math::Vector4>::SetData(Math::Vector4 data)
        {
            memcpy(m_data, data.m_data, sizeof(float) * 4);
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector4>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(float) * 4];
            SetData(Math::Vector4());
            m_type = Type::FLOAT4;
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Vector4>::ShaderVariableTemplate(Math::Vector4 data)
        {
            m_data = new BYTE[sizeof(float) * 4];
            SetData(data);
            m_type = Type::FLOAT4;
        }



        template<>
        inline void HT_API ShaderVariableTemplate<Math::Matrix4>::SetData(Math::Matrix4 data)
        {
            memcpy(this->m_data, data.m_data, sizeof(float) * 16);
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Matrix4>::ShaderVariableTemplate()
        {
            m_data = new BYTE[sizeof(float) * 16];
            SetData(Math::Matrix4());
            m_type = Type::MAT4;
        }

        template <>
        inline HT_API ShaderVariableTemplate<Math::Matrix4>::ShaderVariableTemplate(Math::Matrix4 data)
        {
            m_data = new BYTE[sizeof(float) * 16];
            SetData(data);
            m_type = Type::MAT4;
        }




        typedef ShaderVariableTemplate<int>             IntVariable;
        typedef ShaderVariableTemplate<float>           FloatVariable;
        typedef ShaderVariableTemplate<double>          DoubleVariable;
        typedef ShaderVariableTemplate<Math::Vector2>   Float2Variable;
        typedef ShaderVariableTemplate<Math::Vector3>   Float3Variable;
        typedef ShaderVariableTemplate<Math::Vector4>   Float4Variable;
        typedef ShaderVariableTemplate<Math::Matrix4>   Matrix4Variable;
    }
}
