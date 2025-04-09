plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.nali.scene"
    compileSdk = 35
    ndkVersion = "29.0.13113456"
    buildToolsVersion = "36.0.0"

    defaultConfig {
        applicationId = "com.nali.scene"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"
        ndk {
            abiFilters.add("arm64-v8a")
        }
    }

//    buildTypes {
//        debug {
//            isTestCoverageEnabled = false
//            isMinifyEnabled = false
//        }
//        release {
//
//        }
//    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    buildFeatures {
        prefab = true
    }
    externalNativeBuild {
        cmake {
            path = file("../../CMakeLists.txt")
            version = "3.31.6"
        }
    }
}

dependencies {
//    implementation(libs.appcompat)
}