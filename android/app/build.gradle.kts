plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.nali.scene"
    compileSdk = 35

    defaultConfig {
        applicationId = "com.nali.scene"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    externalNativeBuild {
        cmake {
            path = file("../../CMakeLists.txt")
        }
    }
}

dependencies {
//    implementation(libs.appcompat)
}