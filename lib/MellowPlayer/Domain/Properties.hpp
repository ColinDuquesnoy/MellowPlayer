#pragma once

#include <memory>

#define WRITABLE_PROPERTY(type, name, setter) \
    protected: \
        Q_PROPERTY(type name READ name WRITE setter NOTIFY name##Changed) \
        type name##_; \
    public: \
        virtual const type& name() const \
        { \
            return name##_; \
        } \
    public Q_SLOTS: \
        virtual bool setter(const type& name) \
        { \
            bool ret = false; \
            if ((ret = name##_ != name)) { \
                name##_ = name; \
                emit name##Changed (name##_); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define READONLY_PROPERTY(type, name, updater) \
    protected: \
        Q_PROPERTY (type name READ name NOTIFY name##Changed) \
        type name##_; \
    public: \
        virtual const type& name() const { \
            return name##_ ; \
        } \
        virtual bool updater(const type& name) { \
            bool ret = false; \
            if ((ret = name##_ != name)) { \
                name##_ = name; \
                emit name##Changed (name##_); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define CONSTANT_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ name CONSTANT) \
        type name##_; \
    public: \
        virtual const type& name() const { \
            return name##_ ; \
        } \
    private:

#define READONLY_OBJECT_PROPERTY(type, name, updater) \
    protected: \
        Q_PROPERTY (type* name READ name NOTIFY name##Changed) \
        std::shared_ptr<type> name##_=nullptr; \
    public: \
        virtual type* name() const { \
            return name##_ .get(); \
        } \
        virtual bool updater(const std::shared_ptr<type>& name) { \
            bool ret = false; \
            if ((ret = name##_ != name)) { \
                name##_ = name; \
                emit name##Changed (name##_.get()); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type* name); \
    private:

#define CONSTANT_OBJECT_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type* name READ name CONSTANT) \
        std::shared_ptr<type> name##_; \
    public: \
        virtual type* name() const { \
            return name##_ .get(); \
        } \
    private:
