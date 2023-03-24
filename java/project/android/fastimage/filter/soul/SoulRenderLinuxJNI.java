package project.android.fastimage.filter.soul;


public class SoulRenderLinuxJNI {

    private static SoulRenderLinuxJNI single_instance = null;

    private SoulRenderLinuxJNI() {
        System.loadLibrary("glvndcontext");
    }

    public static SoulRenderLinuxJNI shared() {
        if (single_instance == null) {
            single_instance = new SoulRenderLinuxJNI();
        }
        return single_instance;
    }

    public static native boolean setLinuxGLContext();

    public boolean setLinuxGLContext2() {
        return true;
    }
}
