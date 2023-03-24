package project.android.fastimage.filter.soul;


public class TestSoulRenderLinuxJNI {

    public static void main(String[] args) {
        
        boolean ret = SoulRenderLinuxJNI.shared().setLinuxGLContext();
        if (ret) {
            System.out.println("setLinuxGLContext success!");
        } else {
            System.out.println("setLinuxGLContext fail!");
        }
    }
}
