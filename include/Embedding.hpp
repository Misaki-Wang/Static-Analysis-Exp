#pragma once

#include <vector>
// Define two struct: "VarEmbedding"  "FuncEmbedding"

// Struct to represent the variable's characteristics
struct VarEmbedding {
    int Def;       // Number of times the variable is defined/redefined
    int Use;       // Number of times the variable is used
    int Ptrs;      // Number of aliases the variable has
    int Cfunc;     // Number of functions calling this variable
    int Dvars;     // Number of variables that depend on this variable (optional)

    // Constructor to initialize values
    VarEmbedding(int def = 0, int use = 0, int ptrs = 0, int cfunc = 0, int dvars = 0)
        : Def(def), Use(use), Ptrs(ptrs), Cfunc(cfunc), Dvars(dvars) {}

    // Overloaded operator+ to add two VarEmbedding
    VarEmbedding operator+(const VarEmbedding& other) const {
        return { Def + other.Def, Use + other.Use, Ptrs + other.Ptrs, Cfunc + other.Cfunc, Dvars + other.Dvars };
    }
};

// Struct to represent function's characteristics
struct FuncEmbedding {
    int S_DEF;     // Sum of Def values of all variables in function
    int S_USE;     // Sum of Use values of all variables in function
    int S_PTR;     // Sum of Ptrs values of all variables in function
    int S_FUNC;    // Sum of Cfunc values of all variables in function
    int S_VAR;     // Sum of Dvars values of all variables in function (optional)
    int Count;     // Total number of variables defined in the function

    // Constructor to initialize values
    FuncEmbedding(int s_def = 0, int s_use = 0, int s_ptr = 0, int s_func = 0, int s_var = 0, int count = 0)
        : S_DEF(s_def), S_USE(s_use), S_PTR(s_ptr), S_FUNC(s_func), S_VAR(s_var), Count(count) {}

    // Utility method to add VarEmbedding to FuncEmbedding
    void addVarEmbedding(const VarEmbedding& varEmb) {
        S_DEF += varEmb.Def;
        S_USE += varEmb.Use;
        S_PTR += varEmb.Ptrs;
        S_FUNC += varEmb.Cfunc;
        S_VAR += varEmb.Dvars;
        Count++;
    }

    // Overloaded operator+ to add two FuncEmbedding
    FuncEmbedding operator+(const FuncEmbedding& other) const {
        return { S_DEF + other.S_DEF, S_USE + other.S_USE, S_PTR + other.S_PTR, S_FUNC + other.S_FUNC, S_VAR + other.S_VAR, Count + other.Count };
    }
};

