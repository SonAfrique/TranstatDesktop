#pragma once
#include "../common/defines.h"
#include "HungarianAlg/HungarianAlg.h"

///
/// \brief The SPSettings struct
///
struct SPSettings
{
    track_t m_distThres = 0.8f;
    size_t m_maxHistory = 10;
};

///
/// \brief The ShortPathCalculator class
///
class ShortPathCalculator
{
public:
    ShortPathCalculator(const SPSettings& settings)
        : m_settings(settings)
    {
    }
    virtual ~ShortPathCalculator()
    {
    }

    virtual void Solve(const distMatrix_t& costMatrix, size_t N, size_t M, assignments_t& assignment, track_t maxCost) = 0;
protected:
    SPSettings m_settings;
};

///
/// \brief The SPHungrian class
///
class SPHungrian : public ShortPathCalculator
{
public:
    SPHungrian(const SPSettings& settings)
        : ShortPathCalculator(settings)
    {
    }

    void Solve(const distMatrix_t& costMatrix, size_t N, size_t M, assignments_t& assignment, track_t /*maxCost*/)
    {
        m_solver.Solve(costMatrix, N, M, assignment, AssignmentProblemSolver::optimal);
    }

private:
    AssignmentProblemSolver m_solver;
};

///
/// \brief The SPBipart class
///
class SPBipart : public ShortPathCalculator
{
public:
    SPBipart(const SPSettings& settings)
        : ShortPathCalculator(settings)
    {
    }

    void Solve(const distMatrix_t& costMatrix, size_t N, size_t M, assignments_t& assignment, track_t maxCost);
};
