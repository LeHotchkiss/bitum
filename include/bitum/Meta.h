#ifndef BITUM_METACLASS_H
#define BITUM_METACLASS_H

#include <stdint.h>
#include <stddef.h>

#include "containers/Table.h"
#include "bitum/Constants.h"

#include "hlib/String.h"

#define BitumDeclType(_type)                            \
    template<> struct bitum::meta::SType<_type> {       \
        const uint64_t hash     = 0;                    \
        const char* name        = #_type;               \
    }

#define BitumProperty(_type, _name)                     \
    bitum::meta::CProperty<_type> _name = bitum::meta::CProperty<_type>(#_name, __bitum_get_this());

namespace bitum::meta {
    template <typename var_t> struct SType {
        const uint64_t hash     = 0;
        const char* name        = "(null)";
    };

    template <typename var_t>
    const char* Typename() {
        SType<var_t> data;
        return data.name;
    }

    template <typename var_t>
    const char* Typehash() {
        SType<var_t> data;
        return data.hash;
    }
}

#include "src/engine/meta_types.h"

namespace bitum::meta {
    class IProperty {
        const char* m_name = NULLSTRING;

        public:
            IProperty(const char*);

            const char* Name() const;

            virtual const char* Typename() const = 0;
            virtual uint64_t Typehash() const = 0;

            virtual void* Address() = 0;
            virtual size_t Sizeof() const = 0;
    };
    
    class IMetaclass {
        table_t<hlib::CConstString, IProperty*> m_dProps;

        protected:
            IMetaclass* __bitum_get_this();

        public:
            size_t PropsCount() const;

            IProperty* operator[](size_t);
            IProperty* operator[](const char*);
            IProperty* IndexProperty(size_t);
            IProperty* IndexProperty(const char*);

            void PushProperty(const char*, IProperty*);
    };

    template <typename prop_t> 
    class CProperty final : public IProperty {
        prop_t m_data;

        public:
            CProperty(const char* name, IMetaclass* parent) : IProperty(name) {
                parent->PushProperty(name, (IProperty*)this);
            }

            const prop_t& operator=(const prop_t& other) {
                m_data += other;
                return *this;
            }

            /*
                TODO: implement all of the operators to allow complete shadowing of this wrapper class
            */

            operator prop_t&() {
                return m_data;
            }

            prop_t* operator&() {
                return &m_data;
            }

            prop_t Value() const {
                return m_data;
            }

            prop_t& Reference() {
                return m_data;
            }

            prop_t* Pointer() {
                return &m_data;
            }

            const char* Typename() const override {
                SType<prop_t> data;
                return data.name;
            }

            uint64_t Typehash() const override {
                SType<prop_t> data;
                return data.hash;
            }

            void* Address() override {
                return (void*)&m_data;
            }

            size_t Sizeof() const override {
                return sizeof(prop_t);
            }
    };
}

#endif
