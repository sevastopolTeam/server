#pragma once

#include <exception>
#include <utility>

#include "string.h"

namespace NMaybe {
    class TMaybeException : public std::exception {
    private:
        TString Message;

    public:
        TMaybeException(const TString& message)
            : Message(message)
        {}

        const char* what() const noexcept override {
            return Message.c_str();
        }
    };

    static void OnEmpty() {
        throw TMaybeException("TMaybe is empty");
    }
} // NMaybe

struct TNothing {
    explicit constexpr TNothing(int) noexcept {
    }
};

constexpr TNothing NothingObject{ 0 };

constexpr TNothing Nothing() noexcept {
    return NothingObject;
}

template <class T>
class TMaybe {
public:
    template <class... TArgs>
    constexpr TMaybe(TArgs&&... args)
        : Data_(std::forward<TArgs>(args)...)
        , Defined_(true)
    {}

    constexpr TMaybe(TNothing)
    {}

    template <typename... TArgs>
    T& ConstructInPlace(TArgs&&... args) {
        Clear();
        Init(std::forward<TArgs>(args)...);
        return *Data();
    }

    TMaybe() = default;
    ~TMaybe() = default;

    constexpr TMaybe(const TMaybe&) = default;
    constexpr TMaybe(TMaybe&&) = default;
    constexpr TMaybe& operator=(const TMaybe&) = default;
    constexpr TMaybe& operator=(TMaybe&&) = default;

    TMaybe& operator=(TNothing) noexcept {
        Clear();
        return *this;
    }

    void Clear() noexcept {
        if (Defined()) {
            this->Defined_ = false;
            Data()->~T();
        }
    }

    constexpr bool Defined() const noexcept {
        return this->Defined_;
    }

    constexpr bool Empty() const noexcept {
        return !Defined();
    }

    void CheckDefined() const {
        if (!Defined()) {
            NMaybe::OnEmpty();
        }
    }

    const T* Get() const noexcept {
        return Defined() ? Data() : nullptr;
    }

    T* Get() noexcept {
        return Defined() ? Data() : nullptr;
    }

    constexpr const T& GetRef() const {
        CheckDefined();

        return *Data();
    }

    constexpr T& GetRef() {
        CheckDefined();

        return *Data();
    }

    constexpr const T& operator*() const {
        return GetRef();
    }

    constexpr T& operator*() {
        return GetRef();
    }

    constexpr const T* operator->() const {
        return &GetRef();
    }

    constexpr T* operator->() {
        return &GetRef();
    }

    constexpr explicit operator bool() const noexcept {
        return Defined();
    }

private:
    T Data_;
    bool Defined_ = false;

    constexpr const T* Data() const noexcept {
        return std::addressof(this->Data_);
    }

    constexpr T* Data() noexcept {
        return std::addressof(this->Data_);
    }

    template <typename... TArgs>
    void Init(TArgs&&... args) {
        new (Data()) T(std::forward<TArgs>(args)...);
        this->Defined_ = true;
    }
};
