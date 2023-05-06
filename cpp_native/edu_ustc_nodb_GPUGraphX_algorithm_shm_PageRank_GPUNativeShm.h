/* DO NOT EDIT THIS FILE - it is machine generated */
#include "/usr/lib/jvm/java-11-openjdk-amd64/include/jni.h"
/* Header for class edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm */

#ifndef _Included_edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm
#define _Included_edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm
 * Method:    nativeEnvEdgeInit
 * Signature: ([JJLjava/util/ArrayList;ILorg/apache/spark/graphx/util/collection/shmManager/shmNamePackager/shmReaderPackager;)Z
 */
JNIEXPORT jboolean JNICALL Java_edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm_nativeEnvEdgeInit
  (JNIEnv *, jobject, jlongArray, jlong, jobject, jint, jobject);

/*
 * Class:     edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm
 * Method:    nativeStepMsgExecute
 * Signature: (JLorg/apache/spark/graphx/util/collection/shmManager/shmNamePackager/shmReaderPackager;Lorg/apache/spark/graphx/util/collection/shmManager/shmNamePackager/shmWriterPackager;IIII)I
 */
JNIEXPORT jint JNICALL Java_edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm_nativeStepMsgExecute
  (JNIEnv *, jobject, jlong, jobject, jobject, jint, jint, jint, jint);

/*
 * Class:     edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm
 * Method:    nativeEnvClose
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_edu_ustc_nodb_GPUGraphX_algorithm_shm_PageRank_GPUNativeShm_nativeEnvClose
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
