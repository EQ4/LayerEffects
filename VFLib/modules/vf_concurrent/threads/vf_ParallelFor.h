/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

#ifndef VF_PARALLELFOR_VFHEADER
#define VF_PARALLELFOR_VFHEADER

/*============================================================================*/
/**
  Parallel for loop.

  This uses a ThreadGroup to iterate through a for loop in parallel. The
  following two pieces of code perform identical operations:

  @code

  extern void function (int loopIndex);

  // Serial computation
  //
  for (int i = 0; i < numberOfIterations; ++i)
    function (i);

  // Parallel computation
  //
  ParallelFor().loop (numberOfIterations, &function);

  @endcode

  `function` is a caller provided functor. Convenience functions are provided
  for automatic binding to member or non member functions with up to 8
  arguments (not including the loop index).

  @note The last argument to function () is always the loop index.

  @see ThreadGroup

  @ingroup vf_concurrent
*/
class ParallelFor : Uncopyable
{
public:
  /** Create a parallel for loop.

      It is best to keep this object around instead of creating and destroying
      it every time you need to run a loop.

      @param pool The ThreadGroup to use. If this is omitted then a singleton
                  ThreadGroup is used which contains one thread per CPU.
  */
  explicit ParallelFor (ThreadGroup& pool = *GlobalThreadGroup::getInstance ());

  /** Determine the number of threads in the group.

      @return The number of threads in the group.
  */
  int getNumberOfThreads () const;

  /** Execute parallel for loop.

      Functor is called once for each value in the range
      [0, numberOfIterations), using the ThreadGroup.

      @param numberOfIterations The number of times to loop.

      @param f The functor to call for each loop index.
  */
  /** @{ */
  template <class Functor>
  void loopf (int numberOfIterations, Functor const& f)
  {
    IterationType <Functor> iteration (f);

    doLoop (numberOfIterations, iteration);
  }

  template <class Fn>
  void loop (int n, Fn f)
  { loopf (n, vf::bind (f, vf::_1)); }

  template <class Fn, class T1>
  void loop (int n, Fn f, T1 t1)
  { loopf (n, vf::bind (f, t1, vf::_1)); }

  template <class Fn, class T1, class T2>
  void loop (int n, Fn f, T1 t1, T2 t2)
  { loopf (n, vf::bind (f, t1, t2, vf::_1)); }

  template <class Fn, class T1, class T2, class T3>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3)
  { loopf (n, vf::bind (f, t1, t2, t3, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  void loop (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8, vf::_1)); }
  /** @} */

  // up to 8 ctor args
  template <class Functor, class T1, class T2>
  void run (T1 t1, T2 t2)
  {
  }

private:
  class Iteration
  {
  public:
    virtual void operator () (int loopIndex) = 0;
  };

  template <class Functor>
  class IterationType : public Iteration, Uncopyable
  {
  public:
    explicit IterationType (Functor const& f) : m_f (f)
    {
    }

    void operator () (int loopIndex)
    {
      m_f (loopIndex);
    }

  private:
    Functor m_f;
  };

private:
  class LoopState
    : public AllocatedBy <ThreadGroup::AllocatorType>
    , Uncopyable
  {
  private:
    Iteration& m_iteration;
    WaitableEvent& m_finishedEvent;
    int const m_numberOfIterations;
    Atomic <int> m_loopIndex;
    Atomic <int> m_iterationsRemaining;
    Atomic <int> m_numberOfParallelInstances;

  public:
    LoopState (Iteration& iteration,
               WaitableEvent& finishedEvent,
               int numberOfIterations,
               int numberOfParallelInstances)
      : m_iteration (iteration)
      , m_finishedEvent (finishedEvent)
      , m_numberOfIterations (numberOfIterations)
      , m_loopIndex (-1)
      , m_iterationsRemaining (numberOfIterations)
      , m_numberOfParallelInstances (numberOfParallelInstances)
    {
    }

    ~LoopState ()
    {
    }

    void forLoopBody ()
    {
      for (;;)
      {
        // Request a loop index to process.
        int const loopIndex = ++m_loopIndex;

        // Is it in range?
        if (loopIndex < m_numberOfIterations)
        {
          // Yes, so process it.
          m_iteration (loopIndex);

          // Was this the last work item to complete?
          if (--m_iterationsRemaining == 0)
          {
            // Yes, signal.
            m_finishedEvent.signal ();
            break;
          }
        }
        else
        {
          // Out of range, all work is complete or assigned.
          break;
        }
      }

      release ();
    }

    void release ()
    {
      if (--m_numberOfParallelInstances == 0)
        delete this;
    }
  };

private:
  void doLoop (int numberOfIterations, Iteration& iteration);

private:
  ThreadGroup& m_pool;
  WaitableEvent m_finishedEvent;
  Atomic <int> m_currentIndex;
  Atomic <int> m_numberOfInstances;
  int m_numberOfIterations;
};

#endif
