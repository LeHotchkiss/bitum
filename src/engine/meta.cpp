#include "bitum/Meta.h"

namespace bitum::meta {
    IProperty::IProperty(const char* name) : m_name(name) {}

    IMetaclass* IMetaclass::__bitum_get_this() {
        return this;
    }

    size_t IMetaclass::PropsCount() const {
        return m_dProps.Length();
    }

    IProperty* IMetaclass::operator[](size_t index) {
        return m_dProps.Index(index);
    }

    IProperty* IMetaclass::operator[](const char* name) {
        IProperty** test = m_dProps.At(name);
        return (test == NULL) ? NULL : *test;
    }

    IProperty* IMetaclass::IndexProperty(size_t index) {
        return m_dProps.Index(index);
    }

    IProperty* IMetaclass::IndexProperty(const char* name) {
        IProperty** test = m_dProps.At(name);
        return (test == NULL) ? NULL : *test;
    }

    void IMetaclass::PushProperty(const char* name, IProperty* prop) {
        m_dProps.Insert(name, prop);
    }
}
