
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.



typedef void (*CMLConverterConstructor)(      void** data,
                                         const void* input);


typedef CMLOutput (*CMLConverterEvaluator)(CMLOutput out,
                                            CMLInput in,
                                             CMLSize count,
                                         const void* data);


typedef void (*CMLConverterDesctructor)(      void*  data);


CMLAPI CMLConverter* cmlCreateConverter(
                       CMLConverterEvaluator evaluator,
                     CMLConverterConstructor constructor,
                     CMLConverterDesctructor destructor,
                                 const void* input);


