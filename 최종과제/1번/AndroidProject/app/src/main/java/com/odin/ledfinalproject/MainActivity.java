package com.odin.ledfinalproject;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    // 버튼과 텍스트 뷰 선언
    Button btn_LED_ON;
    Button btn_LED_OFF;
    TextView textView;

    FirebaseDatabase database = FirebaseDatabase.getInstance(); // 파이어베이스와 초기화
    DatabaseReference myRef = database.getReference("BLUE_LED_STATUS"); // BLUE_LED_STATUS를 가르킴

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 여기서 InitializeView, SetListener 실행 선언
        this.InitializeView();
        this.SetListener();
    }

    public void InitializeView() {

        // 버튼과 텍스트뷰를 쓸 수 있게 선언하고 텍스트뷰에 들어갈 글자를 선언함
        btn_LED_ON = (Button)findViewById(R.id.btn1);
        btn_LED_OFF = (Button)findViewById(R.id.btn2);
        textView = (TextView)findViewById(R.id.textView);
        setTitle("전구 원격 조종");
        textView.setText(myRef.getKey());
    }

    public  void SetListener() {
        // read from the Database, addValue Event Listenning
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // ledState에 데이터베이스 저장된 값을 가져와서 텍스트뷰에 보여줌
                String ledState = (String) dataSnapshot.getValue();
                //String value = dataSnapshot.getValue(String.class);

                textView.setText("현재 상태 : " + ledState);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

        // ON_Button Click
        btn_LED_ON.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.BLUE);
                // On버튼을 누르면 ON이라는 값을 셋팅함
                myRef.setValue("ON");
            }
        });

        // OFF_Button Click
        btn_LED_OFF.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.BLACK);
                // On버튼을 누르면 OFF이라는 값을 셋팅함
                myRef.setValue("OFF");
            }
        });
    }
}
