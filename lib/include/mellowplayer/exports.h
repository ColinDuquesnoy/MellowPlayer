#ifndef EXPORTS
#define EXPORTS

#ifdef MELLOW_PLAYER_API
#define DLL_EXPORT  Q_DECL_EXPORT
#else
#define DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORTS

