#pragma once
#include <vector>
#include <memory>

class Type {
        public:
        virtual void print(void) = 0;
};

class ClassType: public Type {
        private:
        std::string name;
        std::vector<std::unique_ptr<Type>> args;
        public:
        ClassType(std::string id);
        void print(void) override;
        void append(std::unique_ptr<Type> type);
};

class PointerType: public Type {
        private:
        std::unique_ptr<Type> inner;
        public:
        PointerType(Type* type);
        void print(void) override;
};

class ArrayType: public Type {
        private:
        std::unique_ptr<Type> element;
        int length;
        public:
        ArrayType(std::unique_ptr<Type> type, int len);
        void print(void) override;
};


